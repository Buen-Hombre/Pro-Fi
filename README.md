# Pro-Fi (ProLoFi) — Plugin Lo-Fi con Estética de Microsoft Excel 97 / Windows 98

Reconstrucción en C++/JUCE del plugin **Lo-Fi** de Avid Pro Tools (`LoFi.aaxplugin`, versión `23.5.0.145`), bautizado como **Pro-Fi**, obtenida mediante ingeniería inversa estática con **REA (`rea-agents@6.5.0`)** sobre el binario nativo (`Contents/MacOS/LoFi`), los binarios DSP de Texas Instruments TMS320C67x+ (`Contents/Resources/LoFiAlgMono.dll` y `Contents/Resources/LoFiAlgStereo.dll`), las tablas de recursos XML (`LoFi.xml`, `LoFiGUI.xml`, `Taper.xml`) y los 25 presets de fábrica (`.tfx`), con interfaz gráfica retro **Microsoft Excel 97 / Windows 98** generada con **Nano Banana**.

---

## 1. Evidencia REA y Artefactos Analizados

| Artefacto | Ruta / Dirección | Hash SHA-256 / Evidencia REA |
| :--- | :--- | :--- |
| Bundle original | `/Library/Application Support/Avid/Audio/Plug-Ins/LoFi.aaxplugin` | `CFBundleVersion = 23.5.0.145`, `Digi` / `LoFi` |
| Binario Universal Mach-O | `Contents/MacOS/LoFi` | SHA-256: `12212c8db0007c0de4bd578aef3c981d7dfc970c8be670093413cf020e8d24d7` (`ev_b83164d562d9eb2b4036345d030be3170b5c7db7969e119b4827083ac5823707`) |
| Slice `arm64` | `LoFi_arm64` | SHA-256: `40dc84c2b30e3df4432af3e48cec1f68f9a23a834c017c1355dcae45688f69e2` (`ev_8871cc9250286e6bad1d4f9e757980f0862a918a0e332c6270ac51b31ea383c1`) |
| Símbolos y Strings | `__TEXT,__cstring` (`0x12f0a0..0x131234`) | `ev_e2a7dc33004e64d45b8b1c5d4339b6dc30c53596bb8fe29296b387997fa48422`, `ev_65fab420a5eee139544907fc3d1e83a1f61712d43ce6a64da259ffcbf199c944` |
| Tablas Constantes | `__TEXT,__const` (`0x124680..0x124780`) | `ev_4e0ff1ced8d249a84348a8bcf67ceb8985d401e07a0ffe7fc34b3ba9ffac7f7b` |
| Algoritmo DSP Mono | `Contents/Resources/LoFiAlgMono.dll` | ELF 32-bit TI TMS320C67x+ (`AlgEntry` en `.text` `0x0000..0x0f20`, `.const` en `0x1080`) |
| Algoritmo DSP Stereo | `Contents/Resources/LoFiAlgStereo.dll` | ELF 32-bit TI TMS320C67x+ (`AlgEntry` en `.text` `0x0000..0x0fa0`, `.const` en `0x1100`) |

---

## 2. Arquitectura del Algoritmo DSP (`AlgEntry`)

Mientras que la sección `__TEXT,__text` (`0x3f00..0x1f38c`) del binario Mach-O anfitrión está envuelta por PACE Eden (`__pbootstrap` / `__povertext`), los módulos DSP `LoFiAlgMono.dll` y `LoFiAlgStereo.dll` compilados con **TI TMS320C6x C/C++ Codegen v7.0.5** se distribuyen **100% sin cifrar y con símbolos completos**, conteniendo la función `AlgEntry` que procesa sub-bloques de 4 muestras por canal.

### Cadena de Procesamiento Exacta (6 Etapas)

1. **Reducción de Sample Rate (Sample & Hold) [`0x00b4..0x0420`]**:
   - Retiene la muestra actual (`state.heldSample`, `*+A31[9]`) durante `decimationStep` muestras (`*+B4[0]`), mapeado en 63 pasos discretos (`__const @ 0x124748 = 63.0`).
2. **Filtro Anti-Aliasing Butterworth de 4.º Orden (2 Biquads en Cascada) [`0x01e8..0x0684`]**:
   - Si `filterEnable != 0` (`*+B8[1]`), procesa las 4 muestras decimadas en precisión doble (`double`) a través de 2 etapas biquad en cascada con coeficientes pre-escalados por `0.5` y doblados en el acumulador mediante `ADDDP X, X, X`.
3. **Detector de Envolvente de Ventana Deslizante (64 muestras) + Generador de Ruido LFSR de 24 bits [`0x0690..0x080c`]**:
   - Mantiene la suma deslizante `runningAbsSum` (`*+A31[20..21]`) de $|\text{in}[n]|$ sobre un buffer circular de 64 muestras (`*+A5[12]`).
   - Extrae el bit 8 (`0x100`) de `(int32_t)(filtered[n] * 2^24)` (`0x41600000_00000000`) y lo desplaza hacia el bit 23 (con extensión de signo a 32 bits) del registro `lfsrState` (`B26`, `*+A31[7]`).
   - Cuando `noiseCoeffs.enable != 0`, modula el registro LFSR por la envolvente normalizada `runningAbsSum * (1/256.0) * envModGain * 2^-23` y lo suma a la señal.
4. **Cuantización de Bits Lineal vs. Adaptativa [`0x0734..0x08b0`]**:
   - Extrae el signo `signBits[i] = (sampleD < 0.0)` (`0x081c: CMPGTDP`) y opera sobre la magnitud $|x|$.
   - En modo **Linear** (`quantType == 0`), el exponente adaptativo es $B_{19} = 0$.
   - En modo **Adaptive** (`quantType == 1`), calcula $v = \lfloor\text{runningAbsSum}\rfloor \gg 3$ y cuenta cuántos desplazamientos cumplen $(v \gg k) == 0$ para $k \in \{0,1,2,3,4\}$, obteniendo $B_{19} \in \{0, 1, 2, 3, 4, 5\}$.
   - Escala la rejilla de cuantización hacia arriba por $2^{B_{19}}$ y de vuelta hacia abajo mediante la tabla `.const` `$P$T0$1` (`{1.0f, 0.5f, 0.25f, 0.125f, 0.0625f, 0.03125f}` en `0x1080` y `0x1246f0`):
     $$|x|_q = \operatorname{trunc}\!\left(|x| \cdot 2^{\text{bits}-1} \cdot 2^{B_{19}} + 0.5\right) \cdot 2^{-B_{19}} \cdot 2^{-(\text{bits}-1)}$$
5. **Distorsión por Tabla Waveshaper de 65 Puntos [`0x08b4..0x0cdc`]**:
   - Escala la magnitud $|x|_q$ por `distCoeffs.drive`, limita el índice a `64.0f` (`0x42800000`), interpola linealmente en precisión doble entre `waveTable[idx]` y `waveTable[idx + 1]` (`*+A5[11]`), mezcla `dryMix` / `wetMix`, y restaura el signo original `signBits[i]`.
6. **Saturación Soft-Knee / Slew Limiter y Medidores de Pico [`0x0a30..0x0ee4`]**:
   - Calcula la diferencia $\text{diff} = x[n] - s_{n-1}$ respecto al estado previo `state.prevSatState` (`*+A31[18..19]`).
   - Si $|\text{diff}| < T$, mantiene la pendiente unitaria ($\Delta = \text{diff}$); si $|\text{diff}| \ge T$, comprime el exceso con pendiente $k$: $\Delta = \operatorname{sgn}(\text{diff})\cdot T + (\text{diff} - \operatorname{sgn}(\text{diff})\cdot T)\cdot k$, actualiza $s_n = s_{n-1} + \Delta$ y aplica `postGain`.
   - Aplica el bypass maestro (`wetGain` / `dryGain`) y actualiza los medidores de pico de entrada y salida (`ABSSP` + `CMPGTSP`), representados en la GUI mediante la ley por tramos de `Taper.xml` (`0..197` píxeles).

---

## 3. Estructura del Proyecto

- [`CMakeLists.txt`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/CMakeLists.txt) — Configuración de compilación para la librería `ProLoFiDSP`, el test `ProLoFiDSPTest` y el plugin JUCE (`VST3`, `AU`, `Standalone`).
- [`Source/AAX_Original/LoFiAlgDefs.h`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/AAX_Original/LoFiAlgDefs.h) — Estructuras exactas del contexto AAX (`LoFiAlgContext`, `LoFiSRFilterCoeffs`, `LoFiQuantCoeffs`, `LoFiNoiseCoeffs`, `LoFiDistCoeffs`, `LoFiSatCoeffs`, `LoFiState`).
- [`Source/AAX_Original/LoFiAlgMono_Decompiled.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/AAX_Original/LoFiAlgMono_Decompiled.cpp) — Decompilación C++ 1:1 de `AlgEntry` (`LoFiAlgMono.dll` y `LoFiAlgStereo.dll`) anotada con direcciones de instrucción.
- [`Source/AAX_Original/LoFiAlgMono_C67x_Disassembly.asm`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/AAX_Original/LoFiAlgMono_C67x_Disassembly.asm) — Desensamblado completo de las 968 instrucciones VLIW de `LoFiAlgMono.dll`.
- [`Source/AAX_Original/LoFi_EffectParameters.h`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/AAX_Original/LoFi_EffectParameters.h) / [`LoFi_EffectParameters.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/AAX_Original/LoFi_EffectParameters.cpp) — Modelo de parámetros, delegados de visualización, ley de medidores `Taper.xml`, generador de coeficientes y los 25 presets de fábrica decodificados de `.tfx`.
- [`Source/DSP/LoFiDSP.h`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/DSP/LoFiDSP.h) / [`LoFiDSP.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/DSP/LoFiDSP.cpp) — Motor DSP multi-bloque que alimenta `AlgEntry_Mono` y `AlgEntry_Stereo`.
- [`Source/PluginEditor.h`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/PluginEditor.h) / [`PluginEditor.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/PluginEditor.cpp) — Interfaz gráfica retro `640x448` con estética **100% Windows 98 (Audio Utility)**: trackbars puntiagudas 3D con marcas de escala, radio buttons `Linear / Adaptive`, perillas rotatorias de plástico gris con marcas radiales, medidores VU en escalera LED segmentada y barra de estado clásica.
- [`Source/ProFiBinaryData.h`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/ProFiBinaryData.h) / [`ProFiBinaryData.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Source/ProFiBinaryData.cpp) — Recursos gráficos PNG de Nano Banana embebidos en memoria binaria.
- [`Tests/test_lofi_dsp.cpp`](file:///Users/oscar/Oscafter%20Dropbox/Oscafter%20Espinosa/MORI%20Sounds/Plugins/ProLoFi/Tests/test_lofi_dsp.cpp) — Suite de verificación de los 25 presets de fábrica.

---

## 4. Compilación

### Compilar y ejecutar la librería DSP y el test de verificación (sin dependencias externas):
```bash
clang++ -std=c++17 -O2 -ISource \
  Source/AAX_Original/LoFiAlgMono_Decompiled.cpp \
  Source/AAX_Original/LoFi_EffectParameters.cpp \
  Source/DSP/LoFiDSP.cpp \
  Tests/test_lofi_dsp.cpp -o ProLoFiDSPTest
./ProLoFiDSPTest
```

### Compilar los plugins VST3 / AU / Standalone con CMake + JUCE:
```bash
cmake -B build -DPROLOFI_FETCH_JUCE=ON
cmake --build build --config Release
```
(O especificando una ruta local de JUCE mediante `-DJUCE_DIR=/ruta/a/JUCE`).

---

## 5. Compilación y Generación del Instalador para Windows

### En Windows localmente (con Visual Studio 2022 y CMake):
1. **Compilar VST3 y Standalone**:
   ```cmd
   cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -DPROLOFI_FETCH_JUCE=ON -DPROLOFI_COPY_AFTER_BUILD=OFF
   cmake --build build --config Release --target ProLoFi_VST3 ProLoFi_Standalone --parallel
   ```
2. **Generar el Instalador `.exe` con Inno Setup**:
   Instala [Inno Setup 6](https://jrsoftware.org/isdl.php) (o con Chocolatey `choco install innosetup`) y ejecuta:
   ```cmd
   "C:\Program Files (x86)\Inno Setup 6\ISCC.exe" /DMyAppVersion=1.0.0 /DBUILD_DIR="build\ProLoFi_artefacts\Release" Installer\windows_installer.iss
   ```
   El instalador se generará en `Installer/dist/Pro-Fi_v1.0.0_Windows_Installer.exe`.

---

## 6. Compilación Automática en la Nube con GitHub Actions

El repositorio incluye workflows automatizados de CI/CD en `.github/workflows/`:

- **Windows CI (`.github/workflows/build_windows.yml`)**:
  - Compila con MSVC en máquinas virtuales de Windows.
  - Genera el plugin `Pro-Fi.vst3` (64-bit) y la app `Pro-Fi.exe`.
  - Construye el instalador ejecutable `.exe` con Inno Setup (`Pro-Fi_v1.0.0_Windows_Installer.exe`).
  - Genera un archivo `.zip` portable.
  - Sube los artefactos para descarga directa en la pestaña **Actions** o en **Releases** al crear un tag (ej. `v1.0.0`).

- **macOS CI (`.github/workflows/build_macos.yml`)**:
  - Compila binarios universales (`arm64` + `x86_64`) en runner macOS.
  - Genera VST3, AU y Standalone listos para distribuir en un paquete `.zip`.

### Cómo usarlo:
1. Sube este repositorio a tu cuenta de GitHub (`git init`, `git add .`, `git commit`, `git push`).
2. Ve a la pestaña **Actions** en tu repositorio de GitHub.
3. Selecciona **Build Pro-Fi for Windows** y haz clic en **Run workflow** (o simplemente haz `push` a la rama principal).
4. Al terminar el trabajo, descarga el instalador listo en la sección **Artifacts** de la ejecución.

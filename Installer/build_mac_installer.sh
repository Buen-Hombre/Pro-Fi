#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_DIR/build/ProLoFi_artefacts"
OUT_DIR="$PROJECT_DIR/Installer"
STAGE_DIR="/tmp/ProFi_Installer_Stage"

echo "=== Building Pro-Fi Universal macOS Installers ==="
rm -rf "$STAGE_DIR"
mkdir -p "$STAGE_DIR"

# 1. Build "Install Pro-Fi.app" (Self-contained Universal Windows 98 Setup Wizard GUI App)
APP_BUNDLE="$OUT_DIR/Install Pro-Fi.app"
rm -rf "$APP_BUNDLE"
mkdir -p "$APP_BUNDLE/Contents/MacOS"
mkdir -p "$APP_BUNDLE/Contents/Resources/Payload"

cat << 'EOF' > "$APP_BUNDLE/Contents/Info.plist"
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>ProFiSetupWizard</string>
    <key>CFBundleIdentifier</key>
    <string>com.morisounds.profi.installer</string>
    <key>CFBundleName</key>
    <string>Install Pro-Fi</string>
    <key>CFBundleDisplayName</key>
    <string>Install Pro-Fi</string>
    <key>CFBundleVersion</key>
    <string>1.0.0</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.15</string>
    <key>NSHighResolutionCapable</key>
    <true/>
</dict>
</plist>
EOF

clang++ -std=c++17 -O2 -arch arm64 -arch x86_64 -mmacosx-version-min=10.15 \
    "$OUT_DIR/ProFiSetupWizard.mm" \
    -framework Cocoa \
    -o "$APP_BUNDLE/Contents/MacOS/ProFiSetupWizard"

cp "$PROJECT_DIR/Resources/Images/profi_assistant_98.png" "$APP_BUNDLE/Contents/Resources/profi_assistant_98.png"
cp -R "$BUILD_DIR/VST3/Pro-Fi.vst3" "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.vst3"
cp -R "$BUILD_DIR/AU/Pro-Fi.component" "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.component"
cp -R "$BUILD_DIR/Standalone/Pro-Fi.app" "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.app"

codesign --force --deep --sign - "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.vst3"
codesign --force --deep --sign - "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.component"
codesign --force --deep --sign - "$APP_BUNDLE/Contents/Resources/Payload/Pro-Fi.app"
codesign --force --deep --sign - "$APP_BUNDLE"
echo "[1/3] Built Universal App Installer: $APP_BUNDLE"

# 2. Build Standard macOS System Installer Package: Pro-Fi_Installer.pkg
PKG_ROOT="$STAGE_DIR/pkg_root"
PKG_SCRIPTS="$STAGE_DIR/scripts"
mkdir -p "$PKG_ROOT/Library/Audio/Plug-Ins/VST3"
mkdir -p "$PKG_ROOT/Library/Audio/Plug-Ins/Components"
mkdir -p "$PKG_ROOT/Applications"
mkdir -p "$PKG_SCRIPTS"

cp -R "$BUILD_DIR/VST3/Pro-Fi.vst3" "$PKG_ROOT/Library/Audio/Plug-Ins/VST3/Pro-Fi.vst3"
cp -R "$BUILD_DIR/AU/Pro-Fi.component" "$PKG_ROOT/Library/Audio/Plug-Ins/Components/Pro-Fi.component"
cp -R "$BUILD_DIR/Standalone/Pro-Fi.app" "$PKG_ROOT/Applications/Pro-Fi.app"

cat << 'EOF' > "$PKG_SCRIPTS/postinstall"
#!/bin/bash
xattr -cr "/Library/Audio/Plug-Ins/VST3/Pro-Fi.vst3" 2>/dev/null || true
xattr -cr "/Library/Audio/Plug-Ins/Components/Pro-Fi.component" 2>/dev/null || true
xattr -cr "/Applications/Pro-Fi.app" 2>/dev/null || true
codesign --force --deep --sign - "/Library/Audio/Plug-Ins/VST3/Pro-Fi.vst3" 2>/dev/null || true
codesign --force --deep --sign - "/Library/Audio/Plug-Ins/Components/Pro-Fi.component" 2>/dev/null || true
codesign --force --deep --sign - "/Applications/Pro-Fi.app" 2>/dev/null || true
killall -9 AudioComponentRegistrar 2>/dev/null || true
exit 0
EOF
chmod +x "$PKG_SCRIPTS/postinstall"

pkgbuild --root "$PKG_ROOT" \
         --scripts "$PKG_SCRIPTS" \
         --identifier "com.morisounds.profi.pkg" \
         --version "1.0.0" \
         --install-location "/" \
         "$OUT_DIR/Pro-Fi_Installer.pkg"
echo "[2/3] Built macOS PKG Installer: $OUT_DIR/Pro-Fi_Installer.pkg"

# 3. Create Distributable ZIP Archive (preserves macOS executable bits & bundles for sharing)
cd "$OUT_DIR"
rm -f "Pro-Fi_Mac_Installer.zip"
ditto -c -k --sequesterRsrc --keepParent "Install Pro-Fi.app" "Pro-Fi_Mac_Installer.zip"
echo "[3/3] Built Distributable Archive: $OUT_DIR/Pro-Fi_Mac_Installer.zip"

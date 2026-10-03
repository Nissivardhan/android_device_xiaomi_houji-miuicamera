# MiuiCamera for houji

## Integration

In `BoardConfig.mk`:

```make
# MiuiCamera
-include device/xiaomi/houji-miuicamera/BoardConfig.mk
```

In `device.mk`:

```make
# MiuiCamera
$(call inherit-product-if-exists, device/xiaomi/houji-miuicamera/device.mk)
```

Leave `camera.package_name` unset. The APK patches provide Leica's client name in its own capture requests.

## Extraction

Run `./extract-files.py /path/to/stock-dump` from this directory.

When migrating from the shared camera fixes, first re-extract `houji`, then re-extract `houji-miuicamera` from the same dump. This removes the old HAL patches and transfers the TS component's generated build module to this tree.

This tree owns `odm/lib64/camera/components/com.mi.node.tsskinbeautifier.so`. Its extractor redirects the plugin's allocation import to `libts_graphicbuffer_shim`, installed beside it in ODM. The shim uses the current vendor `GraphicBuffer` size. It applies to any camera path that executes this TS plugin.

The extractor checks the known TS input and output hashes. Audit a new firmware's TS allocation calls before updating those hashes.

$(call inherit-product, device/samsung/celox/full_celox.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

PRODUCT_DEVICE := celox
PRODUCT_BRAND := samsung
PRODUCT_MANUFACTURER := Samsung
PRODUCT_MODEL := celox

PRODUCT_NAME := lineage_celox
PRODUCT_DEVICE := celox

# Superuser
WITH_SU := true

# We know about rtc
include conf/machine/include/build-extras.inc

IMAGEDIR ?= "${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"
IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    octagon-dvb-modules-${MACHINE} \
    octagon-initrd-${MACHINE} \
    "

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    ${@bb.utils.contains('MACHINE_FEATURES', 'v3d', 'nextv-v3ddriver-${MACHINE}', '',d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'v3d', 'platform-util-${MACHINE}', '',d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'kodi', 'mkswapdev-${MACHINE}', '',d)} \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    ${@bb.utils.contains("GST_VERSION", "1.0", "gstreamer1.0-plugin-dvbmediasink", "gst-plugin-dvbmediasink", d)} \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7ahf-neon"
IMAGE_FSTYPES =+ "tar.bz2"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"

PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-utils"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "octagon-blindscan-utils"

PREFERRED_PROVIDER_virtual/egl = "nextv-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 = "nextv-v3ddriver-${MACHINE}"

MACHINE_FEATURES += "alsa wlan 3dtv switchoff hdmicec blindscan-dvbc kernelwifi extrakernelwifi"

require conf/machine/include/arm/arch-armv7a.inc

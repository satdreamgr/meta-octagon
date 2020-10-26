# We know about rtc
include conf/machine/include/build-extras.inc

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p16"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

QTVER = "-sf8008"
PACKAGECONFIG_GL_pn-qtbase = "gles2 eglfs linuxfb"
PACKAGECONFIG_FB_pn-qtbase = " "

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    octagon-dvb-modules-${MACHINE} \
    octagon-loadmodules-${MACHINE} \ 
    octagon-opengl-${MACHINE} \
    octagon-libs-${MACHINE} \
    octagon-hihalt-${MACHINE} \
    octagon-reader-${MACHINE} \
    octagon-libreader-${MACHINE} \
    octagon-partitions-${MACHINE} \
    octagon-buildimage \
    e2fsprogs-resize2fs \
    gptfdisk \
"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'partitions-by-name' , '', d)} \
"

MACHINE_FEATURES += "videoenhancement switchoff 7segment hdmicec textlcd skins1080 emmc mmc blindscan-dvbs kodi alsa hbbtv-browser-webkit qtstalker"

IMAGE_CLASSES  += "octagon-emmc_image"
IMAGE_FSTYPES += "octagonemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7ahf-neon"

PREFERRED_VERSION_linux-octagon = "4.4.35"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"
PREFERRED_PROVIDER_virtual/egl = "octagon-opengl-${MACHINE}" 
PREFERRED_PROVIDER_virtual/libgles1 = "octagon-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 = "octagon-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-${MACHINE}"

PREFERRED_RPROVIDER_showiframe = "octagon-showiframe-${MACHINE}"
PREFERRED_RPROVIDER_aio-grab = "octagon-grab-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"

require conf/machine/include/arm/arch-armv7a.inc

MACHINE_EXTRA_RRECOMMENDS = " \
    gstreamer1.0-plugin-dvbmediasink \
    gstreamer1.0-libav \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-opus --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGEDIR ?= "octagon/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"
IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"

IMAGE_CMD_octagonemmc_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs1; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs2; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs3; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs4; \
    cp -a ${IMAGE_ROOTFS}/* ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs1/; \
    dd if=/dev/zero of=${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4 seek=${IMAGE_ROOTFS_SIZE} count=60 bs=1024; \
    mkfs.ext4 -F -i 4096 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4 -d ${DEPLOY_DIR_IMAGE}/userdata; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
    if [ -e ${DEPLOY_DIR_IMAGE}/logo-${DISTRO_NAME}.img ]; then \
        cp -f ${DEPLOY_DIR_IMAGE}/logo-${DISTRO_NAME}.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/logo.img; \
    fi; \
    echo ${IMAGEVERSION} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
    mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \ 
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_multiboot_ofgwrite.zip ${IMAGEDIR}/*; \
    zip -j ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -f -f ${DEPLOY_DIR_IMAGE}/*.json; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -Rf ${IMAGEDIR}; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/userdata; \
    "

IMAGE_CMD_prepend = " \
    rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
    "

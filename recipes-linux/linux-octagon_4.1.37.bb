SUMMARY = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
COMPATIBLE_MACHINE = "sf4008"
SRC = "20170227"

inherit kernel machine_kernel_pr

KERNEL_RELEASE = "4.1.37"

SRC_URI[md5sum] = "2ab946924c0b740200bb20f8c49692f0"
SRC_URI[sha256sum] = "a13bc69ec376b568235964103ccb9217efe559b2ebca859f69985f89b91f724a"

LIC_FILES_CHKSUM = "file://${WORKDIR}/linux-${PV}/COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

MACHINE_KERNEL_PR = "r10"

SRC_URI += "http://source.mynonpublic.com/octagon/octagon-linux-${PV}-${SRC}.tar.xz \
    file://defconfig \
    file://proc_meminfo.patch \
    file://0001-Support-TBS-USB-drivers-for-4.1-kernel.patch \
    file://0001-TBS-fixes-for-4.1-kernel.patch \
    file://0001-STV-Add-PLS-support.patch \
    file://0001-STV-Add-SNR-Signal-report-parameters.patch \
    file://blindscan2.patch \
    file://0001-stv090x-optimized-TS-sync-control.patch \
    file://rtl2832-add-support-for-GoTView-MasterHD-3-USB-tuner.patch \
    file://if_port.patch \
    file://t230c.patch \
    file://0001-media-Technisat-SkyStar-USB-HD-DVB-S-S2-too-much-URB.patch \
    file://0003-uaccess-dont-mark-register-as-const.patch \
    "

S = "${WORKDIR}/linux-${PV}"
B = "${WORKDIR}/build"

export OS = "Linux"
KERNEL_IMAGEDEST = "tmp"

FILES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}*"

kernel_do_install_append () {
        install -d ${D}/${KERNEL_IMAGEDEST}
        install -m 0644 ${KERNEL_OUTPUT_DIR}/${KERNEL_IMAGETYPE} ${D}/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION}
}

pkg_postinst_kernel-image () {
        if [ -d /proc/stb ] ; then
		dd if=/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION} of=/dev/mmcblk0p3
        fi
        rm -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION}
        true
}


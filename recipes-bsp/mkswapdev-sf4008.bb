SUMMARY = "swap create extent your memory"
MAINTAINER = "oe-a"
PACKAGE_ARCH = "${MACHINE_ARCH}"
RDEPENDS_${PN} = "util-linux-blkid"

require conf/license/license-gplv2.inc

PV = "1.0"
PR = "r2"

SRC_URI="file://mkswapdev.sh"

do_install() {
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/mkswapdev.sh ${D}${sysconfdir}/init.d/mkswapdev.sh
}

inherit update-rc.d

INITSCRIPT_PARAMS = "start 98 3 ."
INITSCRIPT_NAME = "mkswapdev.sh"

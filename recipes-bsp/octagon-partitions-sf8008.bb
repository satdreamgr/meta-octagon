SUMMARY = "SF8008 partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

SRCDATE = "20200417"
PR = "${SRCDATE}"

S = "${WORKDIR}/patitions"

SRC_URI = "http://define-sw.dyndns.tv/openatv/openpli/${MACHINE}-partitions-${SRCDATE}.zip"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"
do_install[noexec] = "1"

FILES_${PN} = "/usr/share"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/boot.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/apploader.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/emmc_partitions.xml ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/baseparam.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/logo.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/deviceinfo.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
}

addtask deploy before do_build after do_install

SRC_URI[md5sum] = "1d1217eb58a538f87761934e81969bcd"
SRC_URI[sha256sum] = "59d6bb76fc14014132d1701c0b4643a34401df2509e872628554bfb5c5a42ab9"

INSANE_SKIP_${PN} += "already-stripped"

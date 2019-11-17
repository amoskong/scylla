FROM fedora:30
ADD ./install-dependencies.sh ./
ADD ./seastar/install-dependencies.sh ./seastar/
ADD ./tools/toolchain/system-auth ./
RUN dnf -y install 'dnf-command(copr)' \
    && dnf -y install ccache \
    && dnf -y install gdb \
    && /bin/bash -x ./install-dependencies.sh && dnf -y update && dnf clean all \
    && echo 'ALL ALL=(ALL:ALL) NOPASSWD: ALL' >> /etc/sudoers \
    && cp system-auth /etc/pam.d \
    && echo 'Defaults !requiretty' >> /etc/sudoers \
    && sudo dnf downgrade -y https://rpmfind.net/linux/mageia/distrib/5/x86_64/media/core/release/ragel-6.8-5.mga5.x86_64.rpm
CMD /bin/bash

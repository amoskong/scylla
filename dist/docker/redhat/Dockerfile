FROM centos:7

MAINTAINER Avi Kivity <avi@cloudius-systems.com>

ENV container docker

ADD scylla_bashrc /scylla_bashrc

# Scylla configuration:
ADD etc/sysconfig/scylla-server /etc/sysconfig/scylla-server

# Supervisord configuration:
ADD etc/supervisord.conf /etc/supervisord.conf
ADD etc/supervisord.conf.d/scylla-server.conf /etc/supervisord.conf.d/scylla-server.conf
ADD etc/supervisord.conf.d/scylla-housekeeping.conf /etc/supervisord.conf.d/scylla-housekeeping.conf
ADD etc/supervisord.conf.d/sshd-server.conf /etc/supervisord.conf.d/sshd-server.conf
ADD etc/supervisord.conf.d/scylla-jmx.conf /etc/supervisord.conf.d/scylla-jmx.conf
ADD etc/supervisord.conf.d/node-exporter.conf /etc/supervisord.conf.d/node-exporter.conf
ADD scylla-service.sh /scylla-service.sh
ADD node-exporter-service.sh /node-exporter-service.sh
ADD scylla-housekeeping-service.sh /scylla-housekeeping-service.sh
ADD scylla-jmx-service.sh /scylla-jmx-service.sh
ADD sshd-service.sh /sshd-service.sh

# Docker image startup scripts:
ADD scyllasetup.py /scyllasetup.py
ADD commandlineparser.py /commandlineparser.py
ADD docker-entrypoint.py /docker-entrypoint.py
ADD node_exporter_install /node_exporter_install
# Install Scylla:
RUN curl http://downloads.scylladb.com/rpm/unstable/centos/master/latest/scylla.repo -o /etc/yum.repos.d/scylla.repo && \
    yum -y install epel-release && \
    yum -y clean expire-cache && \
    yum -y update && \
    yum -y install scylla hostname supervisor openssh-server openssh-clients && \
    yum -y install http://downloads.scylladb.com.s3.amazonaws.com/rpm/unstable/centos/master/362/scylla/7/x86_64/scylla-666.development-0.20191105.486e3f94d03.el7.x86_64.rpm http://downloads.scylladb.com.s3.amazonaws.com/rpm/unstable/centos/master/362/scylla/7/x86_64/scylla-conf-666.development-0.20191105.486e3f94d03.el7.x86_64.rpm http://downloads.scylladb.com.s3.amazonaws.com/rpm/unstable/centos/master/362/scylla/7/x86_64/scylla-kernel-conf-666.development-0.20191105.486e3f94d03.el7.x86_64.rpm http://downloads.scylladb.com.s3.amazonaws.com/rpm/unstable/centos/master/362/scylla/7/x86_64/scylla-python3-3.7.4-0.20191105.486e3f94d03.el7.x86_64.rpm http://downloads.scylladb.com.s3.amazonaws.com/rpm/unstable/centos/master/362/scylla/7/x86_64/scylla-server-666.development-0.20191105.486e3f94d03.el7.x86_64.rpm
    yum clean all && \
    cat /scylla_bashrc >> /etc/bashrc && \
    mkdir -p /etc/supervisor.conf.d && \
    mkdir -p /var/log/scylla && \
    /node_exporter_install && \
    chown -R scylla.scylla /var/lib/scylla

ENV PATH /opt/scylladb/python3/bin:$PATH
ENTRYPOINT ["/docker-entrypoint.py"]

EXPOSE 10000 9042 9160 9180 7000 7001 22
VOLUME [ "/var/lib/scylla" ]

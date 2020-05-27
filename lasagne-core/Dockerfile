#
# Dockerfile for https://github.com/LASAGNE-Open-Systems/LASAGNE-Core
#

FROM ubuntu:16.04

ARG LASAGNE_VERSION=develop

# Update package repositories and install build-essential

RUN apt-get update && apt-get install -y build-essential git figlet

# clone LASAGNE-Core and dependencies

RUN git clone --depth 1 -b ACE+TAO-6_5_5    git://github.com/DOCGroup/MPC.git /opt/MPC \
 && git clone --depth 1 -b ACE+TAO-6_5_5    git://github.com/DOCGroup/ACE_TAO.git /opt/ACE_TAO \
 && git clone --depth 1 -b DDS-3.13.2       git://github.com/objectcomputing/OpenDDS.git /opt/OpenDDS \
 && git clone --depth 1 -b $LASAGNE_VERSION git://github.com/LASAGNE-Open-Systems/LASAGNE-Core.git /opt/DAF

# Setup environment variables

ENV MPC_ROOT=/opt/MPC \
    ACE_ROOT=/opt/ACE_TAO/ACE \
    TAO_ROOT=/opt/ACE_TAO/TAO \
    DDS_ROOT=/opt/OpenDDS \
    DAF_ROOT=/opt/DAF

ENV TAF_ROOT=$DAF_ROOT/TAF \
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ACE_ROOT/lib:$DDS_ROOT/lib:$DAF_ROOT/lib \
    PATH=$PATH:$ACE_ROOT/bin:$DDS_ROOT/bin:$DAF_ROOT/bin

# build LASAGNE-Core

WORKDIR $TAF_ROOT

RUN cp $DAF_ROOT/bin/build/ace/config.h $ACE_ROOT/ace/config.h \
 && cp $DAF_ROOT/bin/build/ace/default.features $ACE_ROOT/bin/MakeProjectCreator/config/default.features \
 && cp $DAF_ROOT/bin/build/ace/platform_macros.GNU $ACE_ROOT/include/makeinclude/platform_macros.GNU \
 && perl $ACE_ROOT/bin/mwc.pl -type gnuace -workers 2 TAF_CI.mwc \
 && make --jobs 2

ENTRYPOINT ["TAFServer"]

# Override this in user Dockerfile
CMD ["-TAFServices", "DSTO.conf"]

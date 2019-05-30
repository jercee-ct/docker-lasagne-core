FROM lasagneopensystems/docker-lasagne-core:latest

COPY ExampleService.* /opt/ExampleService/

WORKDIR /opt/ExampleService/

RUN perl $ACE_ROOT/bin/mpc.pl -type gnuace ExampleService.mpc -include $DAF_ROOT/MPC/config \
 && make -f GNUmakefile.ExampleService 

CMD $DAF_ROOT/bin/TAFServer -TAFServices ExampleService.conf

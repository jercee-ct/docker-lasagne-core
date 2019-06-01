FROM lasagne-core:develop

COPY ExampleService.* /opt/ExampleService/

WORKDIR /opt/ExampleService/

RUN perl $ACE_ROOT/bin/mpc.pl -type gnuace ExampleService.mpc -include $DAF_ROOT/MPC/config \
 && make -f GNUmakefile.ExampleService 

CMD ["-TAFServices", "ExampleService.conf"]

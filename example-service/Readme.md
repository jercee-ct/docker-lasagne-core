# Example LASAGNE Service

Provided with Dockerfile and docker-compose.yml for ease of use in docker and also a guide of how to implement in your own applications.

To build and run the image, either run `docker build -t lasagne-example-service:1.0.0 .` and `docker run --rm -it lasagne-example-service:1.0.0` from inside this directory,
or install docker-compose and run `docker-compose up` to build and run the image in a container.

Stop with ctrl-c or `docker stop <container>` or `docker-compose stop`.

## The service itself

...is pretty basic, not really even a minimal service, but it has a few of the key concepts of lasagne services, timers, svc threads, queues.
It doesn't have any of the communication mechanisms supported such as DDS and CORBA, it's more just about showing it running in docker.

Bear in mind that for any service supporting networked communications, the ports will need to be opened via docker, or internal docker networks created, which is reasonably straightforward with docker-compose.

all:
	corebuild raytracer.native

run:
	./raytracer.native > output.ppm
	convert output.ppm output.png
	rm output.ppm

clean:
	rm output.ppm output.png raytracer.native

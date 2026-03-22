#!/bin/sh

for i in $(ls | grep gl | sed 's/gl///g'); do
	mv gl-$i gl/$i
done

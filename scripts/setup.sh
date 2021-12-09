#!/usr/bin/env bash

if [ ! -d "/tmp/raytracer_output" ] 
then
  mkdir /tmp/raytracer_output
fi

if [ ! -d "./tmp_output" ] 
then
  ln -s /tmp/raytracer_output ./tmp_output
fi

if [ ! -f "./compile_commands.json" ] 
then
  ln -s build/debug/compile_commands.json ./compile_commands.json
fi

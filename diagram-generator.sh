#!/bin/bash

# Define the directories
input_dirs=("docs/diagrams/MOV/raw" "docs/diagrams/ARITHMETIC/raw")
output_dirs=("/c/dev/ARM7TDMIEmulator/docs/diagrams/MOV/result" "/c/dev/ARM7TDMIEmulator/docs/diagrams/ARITHMETIC/result")

# Loop through each input directory
for i in "${!input_dirs[@]}"; do
  input_dir=${input_dirs[$i]}
  output_dir=${output_dirs[$i]}
  
  # Create the output directory if it doesn't exist
  mkdir -p "$output_dir"
  
  # Process each .puml file in the input directory
  for puml_file in "$input_dir"/*.puml; do
    java -jar /c/dev/ARM7TDMIEmulator/plantuml.jar -tsvg "$puml_file" -o "$output_dir"
  done
done

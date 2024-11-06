# Cat Herder

## Overview
Hello ! So, Cat Herder is a C program where we get to play around with UNIX process management, using `fork` and `exec` system calls. What it does is pretty cool—it sets up a bunch of child processes, then connects them in a pipeline, just like you’d string together commands in the shell.

## Features
- Spins up three child processes to form a pipeline: `kitty -2 | kitty -3 | kitty -4`.
- Manages file descriptors so data flows from one process to another seamlessly.
- Tweaks environment variables for each child based on what they need to work right.
- Keeps an eye on all child processes to make sure they end properly and let the parent know how they did.

## Prerequisites
- You’ll need the GCC compiler.
- A Linux/Unix environment to run this thing.
- Standard UNIX commands and libraries should be available.

### Clone the Repository
First up, you gotta clone the repo to your local machine. Here’s how:

```
git clone https://github.com/yourusername/cat-herder.git
cd cat-herder
```

### Compile the Program
Now, let’s compile the `cat-herder.c` file to make an executable. Just punch in the following command in your terminal:

```
gcc -o cat-herder cat-herder.c
```

Make sure you’re hanging out in the directory that has the `cat-herder.c` file.

## Usage

### Running the Program
To get this baby running, you need to specify an input and an output file, like this:

```
./cat-herder inputfile.txt outputfile.txt
```

replace `inputfile.txt` & `outputfile.txt` with the names of your actual txt files.

### Expected Output
If all goes well, `cat-herder` will churn out an output file as you asked. It will take whatever’s in your input file, run it through the pipeline, and dump it into your outputfile. If something goes wrong, like if you goofed up the input or something breaks during processing, it’ll crash out and tell you what went wrong.

## Contributing
Got ideas to make this better? Jump in! You can:
- Report bugs
- Suggest tweaks
- Throw in some pull requests

Just don’t forget to update tests as you go.

## License
This project is up for grabs under the MIT License - check out the LICENSE.md file for the deets.

# 🐈 Cat Herder 🐈 

# 🐱🐱

## Overview
Hello ! So, Cat Herder is a C program where we get to play around with UNIX process management, using `fork` and `exec` system calls. What it does is pretty cool, it sets up a bunch of child processes, then connects them in a pipeline, just like you’d string together commands in the shell.

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

## Working with kitty and kitty.c

### Understanding kitty
`kitty` is a custom executable we use in our pipeline, it's a sort of simulated `cat` command that interacts with the data piped through our process setup. It's quirky because it only works with stdin and stdout, and it's pretty picky about its environment and open file descriptors.

### Getting kitty
If you don't already have the `kitty` executable, you'll have to ask for it, it is specifically crafted for this project, and is part of university resources that can't be public.

### Compiling kitty from Source
If you've got your hands on `kitty.c`, here's how you can compile it:

```
gcc -o kitty kitty.c
```

This will compile the `kitty.c` source file into an executable named `kitty`, which your `cat-herder` program expects to call.

### Using kitty in the Pipeline
To see `kitty` in action without the full `cat-herder` setup, you can run it directly from the command line. Here’s a quick example:

```
echo "Hello, kitty!" | ./kitty -2
```

This command will echo a string into `kitty` running with the `-2` argument, which, depending on how `kitty` is set up in your version, should manipulate the environment variables or handle input/output in a specific way.

### Integrating kitty with cat-herder
When using `cat-herder`, `kitty` is invoked with different arguments to simulate a pipeline. Each instance of `kitty` modifies its behavior based on the command-line argument (`-2`, `-3`, `-4` etc.). Make sure to review `kitty.c` to understand what each argument is supposed to do and how it affects the handling of file descriptors and environment variables.

### Troubleshooting
If `kitty` doesn’t seem to behave as expected:
- Check that you’re using the correct command-line arguments.
- Ensure there are no extra file descriptors open; `kitty` is very strict about this.
- Verify that the environment variables are set or unset as required for the specific mode you’re testing.

This setup should help you understand how each component interacts within the `cat-herder` program and assist you in debugging or enhancing the project.

## Contributing
Got ideas to make this better? Jump in! You can:
- Report bugs
- Suggest tweaks
- Throw in some pull requests

Just don’t forget to update tests as you go.

## License
This project is up for grabs under the MIT License - check out the LICENSE.md file for the deets.

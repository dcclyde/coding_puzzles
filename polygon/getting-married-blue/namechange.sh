
# Find all files in the current directory that start with gme.
# Change the filenames to start with gmb instead.
# This is a simple example of how to use the rename command.
# The rename command is part of the perl package.
# The perl package is installed by default on most Linux systems.
# If you don't have perl installed, you can install it with the command:
# sudo apt-get install perl

rename 's/gme/gmb/' gme*

# Find all filenames in the current directory that end with an asterisk.
# Change the filenames to remove the asterisk.
# This is tricky because asterisk is a special character in the shell.

rename 's/\*//' *





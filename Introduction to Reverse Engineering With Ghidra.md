# Introduction to Reverse Engineering With Ghidra

This guide is intended to help *anyone* reverse-engineer their first binary using Ghidra. All you will need is 15 minutes and a Windows, Mac, or Linux computer - no prerequisite tools or knowledge.

We'll go over what a binary is (and other technical terms), how to install Ghidra, and finally how to use Ghidra to reverse-engineer a binary.

## Introduction

If you're on a Windows computer, you probably run a lot of `.exe` executables throughout your day - everything from web browsers to games. If you're on a Mac, you'll know them instead as `.app` applications, which are really packages hiding a runnable file inside. And on Linux, you'll be familiar with the extensionless files behind every command you run, like `ls` or `echo`. All of these are examples of **binaries** - files built to run on your operating system.

Have you ever tried opening one of these binaries in a text editor?

No matter the type, you'll find an unreadable mess. In short, the things that run on your computer are written in the language of machines - not code, but an even lower-level, completely unintelligble grouping of zeroes and ones. If we want to read this language, we'll need something to translate for us.

This is what Ghidra is for.

Developed by the NSA, Ghidra allows us to take a binary and approximate the code that produced it. This way, we can read and understand how it works. This process is broadly known as reverse engineering.

At its core, reverse engineering allows us to understand the hidden inner workings of some of the technology that surrounds us. The reasons we might have for doing something like this include picking apart malware, discovering vulnerabilities, and datamining. Later, we will see an example of what we can do with reverse engineering by finding the password to a locked binary.

## Installation

First, let's install Ghidra. Expand the section for your operating system below.

All steps are for Ghidra 11.4.1, which is the latest release at time of writing.

<details><summary>Windows</summary>

1. Download Ghidra from the NSA's GitHub (clicking on link starts download): https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_11.4.1_build/ghidra_11.4.1_PUBLIC_20250731.zip
2. Unzip/extract the folder into the location of your choice (doesn't matter where, just somewhere you'll remember - you can leave it in Downloads if you prefer)
3. Navigate inside the unzipped folder and double-click the file named `ghidraRun.bat` (not `ghidraRun` - note the `.bat` extension)

If you recieve a popup saying something about Java/JDK/javac being unsupported, not found, or needing to be manually chosen, continue on with the steps below:

1. You will need to install JDK. It is currently recommended you use JDK 21, specifically Temurin (clicking on link starts download): https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.8%2B9/OpenJDK21U-jdk_x64_windows_hotspot_21.0.8_9.msi
2. Once finished downloading, double-click the `.msi` installer file to run it
3. In the custom setup screen, click the icon next to `Add to PATH` and ensure that it is set to "Will be installed on local hard drive"
4. Set the other features to "Entire feature will be unavailable"
5. Proceed with the installation. It may ask you for administrator permissions.
6. Try running `ghidraRun.bat` again. You may need to restart your computer for it to work.

If you see a user agreement, Ghidra should now be ready for use! To run Ghidra in the future, just double-click the `ghidraRun.bat` file.

</details>

##

Reverse engineering can be pretty intimidating and hard to get into. Part of the issue is that there are many more extremely deep guides than there are basic ones.
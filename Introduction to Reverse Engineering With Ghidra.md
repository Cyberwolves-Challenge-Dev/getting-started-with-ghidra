# Introduction to Reverse Engineering With Ghidra

This guide is intended to help *anyone* reverse-engineer their first binary using Ghidra. All you will need is 15 minutes and a Windows, Mac, or Linux computer - no prerequisite tools or knowledge.

## Introduction

If you're on a Windows computer, you probably run a lot of `.exe` executables throughout your day - everything from web browsers to games. If you're on a Mac, you'll know them as `.app` applications, which are really packages hiding a runnable file inside. And on Linux, you'll instead be familiar with the extensionless files behind every command you run, like `ls` or `echo`. All of these are examples of **binaries** - files built to run on your operating system.

Have you ever tried opening one of these binaries in a text editor?

No matter the type, you'll find an unreadable mess. In short, the things that run on your computer are written in the language of machines - not code, but an even lower-level, completely unintelligble grouping of zeroes and ones. If we want to read this language, we'll need something to translate for us.

This is where Ghidra comes in. Developed by the NSA, Ghidra allows us to take a binary and approximate the code that produced it. This way, we can read and understand how it works - a process broadly known as reverse engineering.

At its core, reverse engineering allows us to understand the hidden inner workings of some of the technology that surrounds us. The reasons we might have for doing something like this include picking apart malware, discovering vulnerabilities, and datamining. In this guide, we will see an example of what we can do with reverse engineering by finding the password to a locked binary.

## Challenge

Download the `crackme-<os>` binary corresponding to your operating system. For instructions on how to run it, expand the section for your operating system below.

<details><summary>Windows</summary>

Double-click the file. The only trouble you might encounter is if your antivirus hates it for some reason.

</details>

<details><summary>MacOS</summary>

Double-click the file. If it complains about an "untrusted developer":
1. Right-click the file and click "Open" from the menu that appears
2. Click "Run it Anyway"

</details>

<details><summary>Linux</summary>

1. Open a terminal
2. Navigate to the directory where you have the file stored using the command `cd ~/Downloads` (replace with actual path)
3. Give execute permissions to the file using the command `chmod +x crackme-linux`
4. Run the binary with `./crackme-linux`

</details>

After running the file, you should see a prompt asking for a password.

It clearly isn't feasible to guess the password - we must decompile this binary and see how it works. On with Ghidra!

## Ghidra Installation

First, let's install Ghidra. Expand the section for your operating system below.

All steps are for Ghidra 11.4.1, which is the latest release at time of writing.

<details><summary>Windows</summary>

### Windows Installation Guide

1. Download Ghidra from the NSA's GitHub (clicking on link starts download): https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_11.4.1_build/ghidra_11.4.1_PUBLIC_20250731.zip
2. Unzip/extract the folder into the location of your choice (doesn't matter where, just somewhere you'll remember - you can leave it in Downloads if you prefer)
3. Navigate inside the unzipped folder and double-click the file named `ghidraRun.bat` (not `ghidraRun` - note the `.bat` extension)

If you recieve a popup saying something about Java/JDK/javac being unsupported, not found, or needing to be manually chosen, you will need to install JDK. The steps are below:

1. It is currently recommended you use JDK 21, specifically Temurin (clicking on link starts download): https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.8%2B9/OpenJDK21U-jdk_x64_windows_hotspot_21.0.8_9.msi
2. Once finished downloading, double-click the `.msi` installer file to run it
3. In the custom setup screen, click the icon next to "Add to PATH" and ensure that it is set to "Will be installed on local hard drive"
4. Set the other features to "Entire feature will be unavailable"
5. Proceed with the installation. It may ask you for administrator permissions.
6. Try running `ghidraRun.bat` again. You may need to restart your computer for it to work.

If you see a user agreement, Ghidra should now be ready for use! To run Ghidra in the future, just double-click the `ghidraRun.bat` file.

</details>

<details><summary>MacOS</summary>

### MacOS Installation Guide

1. Download Ghidra from the NSA's GitHub (clicking on link starts download): https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_11.4.1_build/ghidra_11.4.1_PUBLIC_20250731.zip
2. Unzip/extract the folder into the location of your choice (doesn't matter where, just somewhere you'll remember - you can leave it in Downloads if you prefer)
3. Navigate inside the unzipped folder and double-click the file named `ghidraRun` (not `ghidraRun.bat`)
4. Mac may warn you about an "untrusted developer". It does this for basically everything. If the menu lacks an option to "run it anyway", right click on the `ghidraRun` file and click "Open" from the menu that appears.

If you recieve a popup saying something about Java/JDK/javac being unsupported, not found, or needing to be manually chosen, you will need to install JDK. The steps are below:

1. It is currently recommended you use JDK 21, specifically Temurin (clicking on link starts download): https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.8%2B9/OpenJDK21U-jdk_x64_mac_hotspot_21.0.8_9.pkg
2. Once finished downloading, double-click the `.pkg` installer file to run it
3. In the custom setup screen, click the icon next to `Add to PATH` and ensure that it is set to "Will be installed on local hard drive"
4. Set the other features to "Entire feature will be unavailable"
5. Proceed with the installation. It may ask you for administrator permissions.
6. Try running `ghidraRun` again. You may need to restart your computer for it to work.

If you see a user agreement, Ghidra should now be ready for use! To run Ghidra in the future, just double-click the `ghidraRun` file.

</details>

<details><summary>Linux</summary>

### Linux Installation Guide

Berhaps a script?

</details>

## Getting Started

Agree to the user agreement. A bunch of windows will open! Feel free to close all of them except for the window with the title "Ghidra: NO ACTIVE PROJECT".

Activities in Ghidra are sorted into "Projects", which contain the files you would like to reverse-engineer. To start, we'll need to make a new project:
1. Click on File > New Project or use the keyboard shortcut `Ctrl+N`
2. Select "Non-Shared Project"
3. Choose a folder to store your projects in. I'd recommend making a new folder just for this purpose in some location you'll remember.
4. Name the project "Practice"
5. Click "Finish"

Now we can import our `crackme` binary from earlier into this project:
1. Click on File > Import or use the keyboard shortcut `I`
2. Select the `crackme` binary from wherever you have it stored
3. Ghidra will automatically identify and apply settings for the file. Just click "OK".
4. Click "OK" or exit the import results summary page. Sometimes the window is too tall to see the OK button; you can drag it down to click the X button instead.

Now the file shows up in the active project! To start reverse-engineering `crackme`, drag its icon from under the active project folder to the little icon of the dragon in the Tool Chest.

## Reverse-Engineering

The screen that opened just now is called the CodeBrowser. It might look a bit overwhelming, but we'll be going over everything you need to know.

Right now, you should see a popup asking if you would like to analyze the file. Click "Yes" and then "Analyze" when the analysis options screen pops up. Analysis should only take a couple of seconds. In the meantime, let's have a quick go-over of the CodeBrowser:


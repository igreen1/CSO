# C Programming Environment Setup
Although C compilers are natively available on nearly all major computing platforms, its closeness to the hardware (and operating system) does not guarantee 100% cross-platform compatibility. In other words, the exact same C program compiled on one machine is not guaranteed to work in exactly the same way when compiled on another machine.

Thus, for your C programming environment, we’re recommending a _virtual machine_ setup rather than something native. There are two strong reasons for this:
1. It guarantees that everyone is programming in a consistent environment and will thus get consistent results
2. You’re going to need a virtual machine anyway—when we go into assembly language programming, we _have_ to all use the exact same operating system and platform

## Ubuntu Virtual Machine Setup
Download and install a virtual machine and set up [Ubuntu Desktop 18.04.4 LTS](https://www.ubuntu.com/download/desktop) on it. Yes, the latest release is 19.10, but the long-term support (LTS) version is preferred for our purposes due to greater stability and compatibility.

Virtual machine possibilities are:
* [VirtualBox](https://www.virtualbox.org)—This is free and will be the one that I’m personally using. Probably the best first option unless you have good reason to go with something else
* [VMWare](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html)—This is Windows only and is a free version of the commercial product
* Built-in Windows virtual machine: Some editions of Windows 10 have a built-in virtual machine called Hyper-V. This is again not verified firsthand, but if you want to give it a shot [here is a web page with instructions](https://www.groovypost.com/howto/create-virtual-machine-windows-10-hyper-v/) (and there may be others)
* Physical machine: Many computers can be set up to boot directly into Ubuntu, so this option will work as well. If you wish to go this route but don’t have a computer that can be used for this purpose or if circumstances keep you from setting up a virtual machine (e.g., laptop is full, compatibility issues, etc.), please contact our Lab Manager, Masao Kitamura, for possible options. He is aware that some students might need this and will have a number of options available, like setting up a Keck lab machine or helping you with an Amazon EC2 host.

Installation should follow the same general procedure: the Ubuntu download is a virtual disk (ISO) file—it’s like a CD/DVD but in the form of a file. You would “insert” this disc into the virtual machine’s virtual drive and “boot” the machine off that “disc.” Installation proceeds just like on a physical computer, except that it is running in a window on the host machine.

Once Ubuntu is up and running, install the GNU C Compiler (_gcc_) by typing <code>sudo apt install gcc</code> at the command line (accessible via the Terminal application).

### VirtualBox/Ubuntu Assorted Tips
* The _.iso_ download from the Ubuntu website is a _virtual disk_. You need to “insert” this disk in your virtual machine’s virtual drive via the **Settings > Storage** dialog. You only need to do this upon installation…just like an actual computer!
* You can choose _Minimal Install_ instead of _Normal Install_ (unless you _really_ want to play some Linux games). This
shortens installation time and will give you a smaller initial virtual hard drive footprint.
* For the _Bidirectional Clipboard_ and _Shared Folder_ features to work, you may need to install something called “Guest Additions.” While your virtual machine is running, choose **Devices > Insert Guest Additions CD Image…** from the menu bar. This adds some supplementary software that makes your virtual machine interact better with the host machine. Reboot the virtual machine after installation completes.
* You might need some tweaking in order to find the “sweet spot” of performance for your virtual machine. Start by running VirtualBox by itself (no other apps on your host machine) and also giving your virtual machine a decent chunk of memory (2GB if you can spare it, with additional graphics memory too). If things feel sluggish, gradually lower settings until things are
running comfortably. The beauty of a virtual machine is that upgrades/downgrades are just mouse clicks away!

## “Native” C Setup
If, for some reason, you prefer to wait on setting up a virtual machine until we move to assembly language programming, a native `gcc` compiler for the following platforms as follows:
* macOS—Download and install Xcode from the Mac App Store or from their [developer website](https://developer.apple.com/xcode/) (free signin required)
* Windows—Download and install [Cygwin](http://www.cygwin.com) or [MinGW](http://www.mingw.org)
You might know of other options…if you’re wondering if one will work, ask me.

moot and groot
==============
Two utilities that make using life easier for root.
moot allows for secure builds within root's home directory.
groot trains programs and scripts to not cower in fear of your almighty rootness.

Install
-------
Just run:
```
make install
```

Uninstall with:
```
make uninstall
```

Usage
-----
The primary aim of moot is to be used to securely build software which root has downloaded and placed within its home directory.
Simply `cd` to the source directory and invoke `moot`. You will be given a shell with a randomly generated user with full access to the current directory, but restricted access otherwise.
This way you can run a build without the distinct possibility of wrecking your whole system. In fact it should be more secure than running a build as a normal user.
By default it gives the generated user group access, but the argument `-g ""` will cancel the group assignment and leave the user with *only* access to the current directory (a fake unwriteable tree will be generated above it in case of an untraversable directory path).

Do not invoke `moot` under a high level directory, as it will take some time to assign permissions as well as break existing owner/groupship of files.
Full details of advanced usage are given when invoking `moot -h`.

The primary aim of groot is to get software to stop refusing to run because UID is 0. Invoking `groot` will give you a shell in which bash scripts think the UID/EUID is 1, and therefore should not be able to detect root via the normal means. Also any program launched will have its getuid/geteuid system calls overidden by libuid. libuid will check /etc/uid.conf for lines of the format "program_name uid euid" and override the values accordingly. An example for vlc is given by default, which tricks vlc into thinking EUID is 1, and therefore not root. In this manner programs that complain about root can be fixed, and programs that require superuser will still know the correct uid (and will not complain the other way around).

Full details are given when invoking `groot -h`.

Bugs
----
Currently `moot` will chown *all* files/directories in the current directory to the new user, and chown them *all* back to your current user (as both owner and group) at the end of the session. Therefore it should not be used if it is important that some files and directories maintain a special owner or group. I have some solutions in mind, but they would likely affect the speed at which the command may be used and special permissions are not likely in the normal use case.

Why
---
The normal security recommendation is to run an unprivileged user and use `sudo` for administration tasks that require root. The reason being that any program you run as root has that full capability passed to it. root has ownership over /, and therefore a rogue script can destroy the whole system. Running as a normal user on the other hand, a rogue script can *only* destroy your entire user directory. Right, no biggie then. That's only all your irreplaceable personal files. User-based permissions work great on a truly multi-user system, but the real concern for most systems is *applications*. Your browser should not have the capability to destroy your user directory, nor your text editor, nor your calculator.

moot is not the full answer to this problem. But it is a simple utility that renders at least part of the standard security recommendation moot. It offers a convenient method of narrowing down the scope of potentional mass destruction.
As for groot, I hate that any application would try to enforce its own dogma upon its users. It is insane to think that the superuser should ever be less capable than that of a normal user.

Licensing
---------
This project is covered under [GPLv3 (or any later version)](http://www.gnu.org/licenses/gpl.html).

Details in [License](LICENSE.md).
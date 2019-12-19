Objective: To implement the functionalities of the shell

The additional features added are:

->setenv and unsetenv

these are used to initialize and delete the environment variables

->kjob

it is used to give a particular job a signal.Implemented using kill()

->fg and bg

﻿Used to bring a background job to foreground and a stopped backgroung job to running.Implemented using tcsetpgrp() and kill().

->overkill

Used to kill all background jobs.Implemented by using kill() a on all background processes.

->ctrl-z and ctrl+c

Implemented previously during the functioning of foreground and backgroung processes.

->jobs

Defines all the available jobs.Implemented using a linked list holding all processes and the /proc directory.



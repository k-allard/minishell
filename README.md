# Minishell
Bash implementation 

_This is a collaborative project @[kallard](https://github.com/k-allard) && @[cwindom](https://github.com/cwindom) (aka fastest shell team)_

## Usage

1. Type ``make`` command in the root directory of this project
2. Launch *fastestshell* by typing ``./minishell``

## What is does?

:white_check_mark: Builtin commands:

* ``echo`` with option ``-n``
* ``cd`` with a relative or absolute path
* ``pwd`` without any options
* ``export`` without any options
* ``unset`` without any options
* ``env`` without any options and any arguments 
* ``exit`` without any options

:white_check_mark: ``;`` commands separator

:white_check_mark: ``’`` and ``"`` work like in bash except for multiline commands

:white_check_mark: Redirections ``<`` ``>`` ``>>`` except for fd aggregation

:white_check_mark: Pipes ``|``

:white_check_mark: Environment variables ``$`` followed by characters

:white_check_mark: Last exit code ``$?`` 

:white_check_mark: Signals ``ctrl-C``, ``ctrl-D`` and ``ctrl-\`` have the same result as in bash

## Examples

![video_1](https://github.com/k-allard/imgs/blob/master/minishell_1.gif)

![video_2](https://github.com/k-allard/imgs/blob/master/minishell_2.gif)

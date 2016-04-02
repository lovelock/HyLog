## Hylog - A HYgh Performance Logger for PHP as an Extension

A flexible and high performance PHP extension for logging, which is compatible with [PSR-3](http://www.php-fig.org/psr/psr-3/). 

## Requirements
- PHP 7+

## Features

1. High performance.
2. Flexible configuration with an appropriate one by default.
3. Various methods to change configurations at run time.
4. Analysing toolset for the log files it generates.

## Installation

1. Retrieve the latest source code of the extension.

    `git clone git@github.com:lovelock/HyLog.git`

2. Compile the source code.

    ```
    cd HyLog
    phpize
    make && sudo make install
    ```

3. Add lines to `php.ini`.

    ```
    extension=hylog.so
    ```

4. Restart PHP-FPM to load the extension.

    ```
    sudo systemctl restart php-fpm
    ```

## Configuration

## Methods

## Analysing

## Examples

## Benchmarks

## Contributions

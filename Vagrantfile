# -*- mode: ruby -*-
# vi: set ft=ruby :

#
# Vagrant configuration for Exercise 4, SE 3800
# Author: Robert W. Hasker
#
# This installs Ubuntu 16.04, Java 8, junit4, maven, ant, Jenkins, etc.
#

Vagrant.configure(2) do |config|
  config.vm.box = "bento/ubuntu-16.04-i386"

  config.vm.provider :virtualbox do |vb|
    # Uncomment following to help diagnose problems when vagrant up fails
    #vb.gui = true
  end

  # Forward ports for Jenkins
  config.vm.network "forwarded_port", guest: 6060, host: 6060
  config.vm.network "forwarded_port", guest: 8080, host: 7070
  # 
  # This allows accessing Jenkins as http://localhost:7070/
  # see: https://wiki.jenkins-ci.org/display/JENKINS/Installing+Jenkins+on+Ubuntu
  #

  # install packages
  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update
    # upgrade; this is normally "sudo apt-get -y upgrade", but the following
    #    avoids problems with Ubuntu setup
    sudo DEBIAN_FRONTEND=noninteractive apt-get -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" upgrade
    echo "US/Central" | sudo tee /etc/timezone
    sudo apt-get install -y g++ cmake git
    sudo apt-get install -y default-jdk         # required for Jenkins
    sudo apt-get install -y libgtest-dev        # GoogleTest
    # the following help ensure time and date sync right between windows & Linux
    sudo apt-get install -y dkms virtualbox-guest-additions-iso

    # set up GoogleTest
    cd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    sudo cp *.a /usr/lib

    # set up Jenkins
    cd /vagrant
    # steps from https://wiki.jenkins-ci.org/display/JENKINS/Installing+Jenkins+on+Ubuntu
    wget -q -O - https://jenkins-ci.org/debian/jenkins-ci.org.key | sudo apt-key add -
    sudo sh -c 'echo deb http://pkg.jenkins-ci.org/debian binary/ > /etc/apt/sources.list.d/jenkins.list'
    sudo apt-get -y update
    sudo apt-get -y install jenkins
    cd /usr/local/bin
    sudo wget https://faculty-web.msoe.edu/hasker/se3800/ex/4/setup-jenkins-keys
    sudo chmod +x setup-jenkins-keys
  SHELL
end

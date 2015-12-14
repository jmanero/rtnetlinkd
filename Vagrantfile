# -*- mode: ruby -*-
# vi: set ft=ruby :

require 'fileutils'
COOKBOOK_PATH = '.vagrant/vendorcookbooks'
FileUtils.mkdir_p(COOKBOOK_PATH)

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure(2) do |config|
  config.vm.box = 'ubuntu-14.04-provisionerless'

  # config.vm.network "forwarded_port", guest: 80, host: 8080
  # config.vm.network "private_network", ip: "192.168.33.10"
  # config.vm.network "public_network"

  config.vm.synced_folder '.', '/home/vagrant/src'

  # config.vm.provider "virtualbox" do |vb|
  #   vb.gui = true
  #   vb.memory = "1024"
  # end

  config.omnibus.chef_version = 12.5

  config.vm.provision :host_shell do |shell|
    shell.cwd = 'cookbook'
    shell.inline = "berks vendor ../#{COOKBOOK_PATH}"
  end

  config.vm.provision :chef_solo do |chef|
    chef.cookbooks_path = COOKBOOK_PATH
    chef.run_list = ['recipe[rtnetlinkd::default]']
  end
end

#
# Cookbook Name:: rtnetlinkd
# Recipe:: default
#
# Copyright (C) 2015 YOUR_NAME
#
# All rights reserved - Do Not Redistribute
#
include_recipe 'apt::default'

apt_repository 'nodejs' do
  uri 'https://deb.nodesource.com/node_0.12'
  components ['main']
  distribution node['lsb']['codename']
  key 'https://deb.nodesource.com/gpgkey/nodesource.gpg.key'
end

package 'build-essential'
package 'ntp'
package 'nodejs'

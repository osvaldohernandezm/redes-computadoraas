mcsquintanillasg@gmail.com
sudo vim /etc/network/interfaces
//ponemos esto en el documento
auto lo
iface lo inet loopback

auto wlan0
iface wlan0 inet dhcp

auto eth1
iface eth1 inet static
address 192.168.0.1
netmask 255.255.255.0
broadcast 192.168.0.255
//cerramos archivo y con el siguiente comando reiniciamos el servidor de red
sudo /etc/init.d/netwoking restart
/*next step*/
echo 1 > /proc/sys/net/ipv4/ip_forward//activamos ipforwart
/*next pass*/
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE//activar nat
/*next pass*/
sudo vim /etc/dnsmasq.conf
//bucamos,descomentamos y modificacmos
listen-address=192.168.0.1
bind-interfaces
dhcp-range=192.168.0.2,192.168.0.254,12h
/etc/init.d/dnsmasq restart

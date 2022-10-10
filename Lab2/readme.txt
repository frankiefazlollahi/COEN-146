# Name: Frankie Fazlollahi
# Date: 1/13/2022
# Title: Lab2
# Description: My observations for steps 1,2,4,5
Step 1)
        a. When running the netstat command it displayed a list of all active internet connections and the TCP/UDP ports that on which the compter is listening. It also displayed all of the active UNIX domain sockets.
        b. When running the ifconfig command  it displayed the configuration of all active interfaces. It can be used to enable/disable an interface and troubleshoot configurations.
        c. When running the hostname command it returned the hostname of my computer. It can be used to change the hostname.
        d. When running the ping command in combination with a destination (such as a website) it sends an ICMP ECHO_REQUEST and receives an ECHO_RESPONSE from the host. Ping calculates the time it takes to send a request and receive a response. It can be used for understanding the response time between servers and computers to see the speed of a connection.
        e. The traceroute command shows the path that a packet takes when sending information to a destination. It also tells how long it took to send the information. It can be used to understand where the packet is spending a lot of time while traveling.
        f. When running the telnet command with a specified IP address and port number, it tells us whether it is open or not to run programs remotely and conduct administration.
        g. The host/dig command allows us to ask for information about DNS reccords (such as host addresses, mail exchanges, and name servers). It can be used for verifying and troubleshooting DNS problems and displaying answers from a requested server.
        h. The route command displays and allows us to manipulate the IP routing table. It can be used for setting up static routes to a specific host or networks through an interface.
        i. The arp command manipulates or displays the kernel's IPv4 network neighbor cache. It can be used to add, delete, or display current content.

Step 2) Packet size for pinging: 1024
North America host: www.cnn.com
	Packet Loss: 0%
	Average RTT: 4.381 ms
	Explanation: Since this is a North American server it is close to where I am sending the ping from so there was no packet loss and it had a quick RTT.
Asia host: www.china.org.cn
	Packet Loss: 0%
        Average RTT: 4.656 ms
        Explanation: Since this is in China, it is further than the North American host so its RTT was slower than the NA host ping but it was still strong enough to have no packet loss.
Europe host: euagenda.eu
	Packet Loss: 0%
        Average RTT: 166.546 ms
        Explanation: This the pings to thie EU server was much slower than the pings to the other two locations, likely due to a slower connection to EU than China and NA. The connection was still good enough that there was no packet loss.

Step 4)
	a. After typing telnet gaia.cs.umass.edu 80 the terminal output is as follows:
		Trying 128.119.245.12...
		Connected to gaia.cs.umass.edu
		Escape character is '^]'.
	b. It returned an index page with a lot of information.
	c. We get the index file through the path "/kurose_ross/interactive/index.php".
	   The client runs HTTP version 1.1.
	   The formats of text and images: tables, <p>, lists, links, and images (.jpg).

Step 5) I was able to connect to all three hosts using port 80 but when trying to use port 3389 all of the attempts to connect to each of the hosts timed out. When trying to use port 3389 it said "Trying 151.101.189.67..." then after that attempt timed out it said "Trying 2a04:4e42:2d::323..." for www.cnn.com. Similar outcomes came from the other two hosts. However, unlike the other two hosts, the www.china.org.cn  host tried several attempts to connect instead of just 1 attempt for each.	

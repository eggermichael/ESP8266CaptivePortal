/*
 * Captive Server
 * this is based on Captive Portal by: M. Ray Burnette 20150831
 *  I just changed it a little..
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>                 
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>IT Helpdesk</title></head><body>"
                      "<img src=\""
"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAYABgAAD/4QNeRXhpZgAATU"
"0AKgAAAAgABgESAAMAAAABAAEAAFEAAAQAAAABAAAAAFEBAAMAAAABAAEAAFECAAE"
"AAAMAAAAAVlEDAAEAAAABAAAAAFEEAAEAAAAB/AAAAAAAAAAAAAAAADMAAGYAAJkA"
"AMwAAP8AKwAAKzMAK2YAK5kAK8wAK/8AVQAAVTMAVWYAVZkAVcwAVf8AgAAAgDMAg"
"GYAgJkAgMwAgP8AqgAAqjMAqmYAqpkAqswAqv8A1QAA1TMA1WYA1ZkA1cwA1f8A/w"
"AA/zMA/2YA/5kA/8wA//8zAAAzADMzAGYzAJkzAMwzAP8zKwAzKzMzK2YzK5kzK8w"
"zK/8zVQAzVTMzVWYzVZkzVcwzVf8zgAAzgDMzgGYzgJkzgMwzgP8zqgAzqjMzqmYz"
"qpkzqswzqv8z1QAz1TMz1WYz1Zkz1cwz1f8z/wAz/zMz/2Yz/5kz/8wz//9mAABmA"
"DNmAGZmAJlmAMxmAP9mKwBmKzNmK2ZmK5lmK8xmK/9mVQBmVTNmVWZmVZlmVcxmVf"
"9mgABmgDNmgGZmgJlmgMxmgP9mqgBmqjNmqmZmqplmqsxmqv9m1QBm1TNm1WZm1Zl"
"m1cxm1f9m/wBm/zNm/2Zm/5lm/8xm//+ZAACZADOZAGaZAJmZAMyZAP+ZKwCZKzOZ"
"K2aZK5mZK8yZK/+ZVQCZVTOZVWaZVZmZVcyZVf+ZgACZgDOZgGaZgJmZgMyZgP+Zq"
"gCZqjOZqmaZqpmZqsyZqv+Z1QCZ1TOZ1WaZ1ZmZ1cyZ1f+Z/wCZ/zOZ/2aZ/5mZ/8"
"yZ///MAADMADPMAGbMAJnMAMzMAP/MKwDMKzPMK2bMK5nMK8zMK//MVQDMVTPMVWb"
"MVZnMVczMVf/MgADMgDPMgGbMgJnMgMzMgP/MqgDMqjPMqmbMqpnMqszMqv/M1QDM"
"1TPM1WbM1ZnM1czM1f/M/wDM/zPM/2bM/5nM/8zM////AAD/ADP/AGb/AJn/AMz/A"
"P//KwD/KzP/K2b/K5n/K8z/K///VQD/VTP/VWb/VZn/Vcz/Vf//gAD/gDP/gGb/gJ"
"n/gMz/gP//qgD/qjP/qmb/qpn/qsz/qv//1QD/1TP/1Wb/1Zn/1cz/1f///wD//zP"
"//2b//5n//8z///8AAAAAAAAAAAAAAAD/2wBDAAIBAQIBAQICAgICAgICAwUDAwMD"
"AwYEBAMFBwYHBwcGBwcICQsJCAgKCAcHCg0KCgsMDAwMBwkODw0MDgsMDAz/2wBDA"
"QICAgMDAwYDAwYMCAcIDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDA"
"wMDAwMDAwMDAwMDAwMDAz/wAARCAAoADIDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQE"
"AAAAAAAAAAAECAwQFBgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIh"
"MUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q"
"0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmq"
"KjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl5ufo6erx8vP"
"09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREAAgEC"
"BAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRC"
"hYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dX"
"Z3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMn"
"K0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD4s8C/8Fk9"
"U+F/wwi0ieHTNc8Q20dxFBrkt1LJcRJJHiFjGQwkeOXLHdhWRI12ggsYvAf7T2u/t"
"AfFayg1SNY47DTlnluID532yQtxJI5I8ssCxGRktu6YOfkX9lb4b+EfG37VHh/wz4"
"21aXTfCdxfhbx4HzNcrjK2yOuVV5GwhO7AOcNnaa/Sz4vfD39nX4MeHdH134c6iPC"
"a31wkElnqOqNNHqsaoU+SSViFaIbifmCYLD75UH4fPcJhsPGNCMXKTV1pofVZJTxF"
"eosTKS5YvuQ2U8VrE0ssiQxxqTJI3RFB5JPYADPJHQ9+nxv+0D+2/wCKvFeuzR+E9"
"WuNH8Pxlordo8b7pVOWkc8soLDhWwcFcA8k+3ftifHLwTpP7PGrL4Y8RabqWtXWy2"
"a3tdTt7hpYXJWXCh2JXZxnaCBk57V85fEz9mDVPh94l0/Rri3kub68to9VkjsZftV"
"xZSGENIs0SkPHICOpwRlApOa4sky2lSftsSr32R9JmWIq1U6WFe276n19/wAEy/8A"
"gsmfFfxN8O/D/wCOlrNqcGpalbWFp4uj1C5hnt5WmVoVvYkcROm7aDKgUjCs4kO9q"
"4z/AIKAaMLvWvDsjMzN/wAINZIVb+HEt2COOmMd+nTnrXwz4w8Lf8IfPNIJPLZl8q"
"SMxDAI3ZG4jJIKk7iAVIU4PGPs/wCO/iiD4i+FfAeoQ3DXP2r4d6Wbg+Ysk3mb7rf"
"5hX/loSckEd+duQK9fNaMU41ae1n8jx8rlNScKu59W2nh27NrHsbxpt2Db9nu7RYc"
"Y/gDfMF9AecYzRXWaZE39m2/y/8ALJelwcdBRXw7xU7n0v1LzPxD+JdrqWi/EWSaS"
"K40u+094BKyyos1vIMbW/dhArfKGUKBgAdwTX098DtN174w2s1v8PvgD4u8dTTsJB"
"eyxz3UCDakZBaMpGANmOo+6M8gY98/Y7/4JSWn7X/7ef8AaXia9hu/AujTW+reJNP"
"WKWKO6uGVUtbN5iQVWdkldjw6woxGfMVq/bOLQPDb+E7Vraxt4dMt0jSw0rToIYIb"
"WNkBSNAoEaIqnjbxjAHGK/Qs4zahHkjy80vU+OyvLK75mmox+/8AQ/nC+JX7DHxe8"
"CfGHw3HqXhXQ/DHiDWIy8+lW+oQXEyxo7CSaSNZJEXEbAmMPuUYJUZUt9qXunfDH4"
"rePPGOs6hDqkWvMDpkN3ab4wnmp+/ZNp8uOZE8sKzgby3ynIxX6E/FP4Ox+MRNqOr"
"fD26hgsS4iv7uAJcwI3yMTIyowDLtGd2D8hOcLXxx+yhdWP7Cv7TnizWJvBel+JPs"
"umRGDVbqyE99YW4lk+0Rx+UJJYppWuoo8xbw6pgsEJx8xUx88VOMZLl5drH2GX06W"
"BpScfebd9Tlf2f/ANj74e/EDxX4P1CxSPxfpPw9vZdQkk1l45rTU7kqVZTbgIJYUZ"
"RhBtXeCzFlJR/n/wDa2HhfQPjN/YPha30qxsdC0KHTzY2B5snW7u9sT92ZYjEAzFi"
"Rt5J6fT3h/wDbKvPj1+3R4n8QaX4dh8P+GbyyggCNZraNe+W5je4EOAVf94pIbLmN"
"C7H5Cq+7fED4G+G/2q/2cfEvhe+023vvE3hm3vJ9Gu7eLddWrpF5sEhf5XVZ2kEXl"
"Zw4ic8nASo1ZxvSm29CsVTp1IxxEIpO+p8hH40yodsfiR4I14WMQ2jeWOy5KknHTJ"
"JNFclpjyJpturWN8zLEoLHSU5OBz/rR/IfQUV8/wC0R6XsY9z9Pf2U/gBafsifAnT"
"dD85dR1qS4n17xFfqf3mralKhluJgeu1dixRg8rFDEMkgmux+FHxLs/CfjL/hGbqa"
"e5udNlljtIvnVFhdUMBwgaRmeAIAsY4CuWKg4JRXpVqkpTcnuzx8PSiocq6Hh37dP"
"xl+GfgP9qvSbnxD4tjv7i28PXNnd6VJrb6bpWlMZrqxga4syqmRZLmeQGZpozH9lj"
"lzsUsOb8KeMfhrovwivvDral4v0X4ia34I00f2ZJdvb61ON9w8VystzgW9xOscjyG"
"V9wQQExQshjoor2fqdNUeZXuVh8fVnVjB2stNjl/2pP2btJ8GfsreHfiBdXl3rnil"
"j9pu9ZuruGQxSm5Z/Kd4QIX8okRLhQAICORk12f7KGk33w0+Ouj+Ir3Xre+tNa0l9"
"EmJsFtprmaW+N3A9zIHKzeW5MEZCoVRwu5gAAUV5dRuCck9TuVGFVz51sed/E//AI"
"JS6trPxL8RXmjzNb6TdanczWURlkPlwNKxjXIbHCkCiiivO9hAn20+5//Z"
                      "\">"
                      "<p><h1>Have you tried</h1><p>turning it off and on again?"
                      "</body></html>";


void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("WhenYourWIFIDoesNotWork");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  
}





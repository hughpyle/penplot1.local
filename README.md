Pen Plotter

This machine is a print server for HPGL pen plotters.

Processes:
* ipp-server, runs the main print-server.
  This also runs a trivial webpage that redirects to the
  main (port 80) webpage.

* apache, webserver.
  Home is in /var/www/html/
  Homepage at http://penplot1.local/

There's also an Avahi service file at
  /etc/avahi/services/lvp16.service
that describes the printer for AirPrint (Bonjour/Zeroconf) discovery.

The IPP server runs on the standard port 631, with authbind,
enabled by
    sudo touch '/etc/authbind/byport/!631'
    sudo chown pi:pi '/etc/authbind/byport/!631'
    sudo chmod 755 '/etc/authbind/byport/!631'
and then run with
    authbind --deep python -m ippserver --host penplot1.local --port 631 save /tmp

The server is actually run with a crontab on ./bin/ipp
and the IPP server then runs 'print-hpgl' to print the files.


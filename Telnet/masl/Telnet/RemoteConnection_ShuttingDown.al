terminal state Telnet::RemoteConnection.ShuttingDown () is
begin

  // TODO gracefully close the socket
  
  // unlink from terminal
  unlink this R3 this->R3.provides_communication_channel_for.NetworkVirtualTerminal;
  
  // delete self
  delete this;
  
end state;

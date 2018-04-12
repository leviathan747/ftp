state Telnet::RemoteConnection.ReportingError ( code: in error ) is
begin
  // TODO log error
  Print~>error( code );
  generate RemoteConnection.done() to this;
  
  // TODO clean up
end state;

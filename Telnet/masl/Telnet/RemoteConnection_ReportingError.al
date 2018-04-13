state Telnet::RemoteConnection.ReportingError ( code: in error ) is
begin
  // TODO log error
  Print~>error( code );
  generate RemoteConnection.close() to this;
  
  // TODO clean up
end state;

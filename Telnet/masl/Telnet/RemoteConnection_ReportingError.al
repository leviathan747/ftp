state Telnet::RemoteConnection.ReportingError ( code: in error ) is
begin

  // TODO log error
  Print~>error( code );
  generate RemoteConnection.close() to this;

end state;

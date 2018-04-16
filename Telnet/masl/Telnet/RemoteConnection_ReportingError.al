state Telnet::RemoteConnection.ReportingError ( error: in error ) is
begin

  // log error
  Logger::error( "Telnet::RemoteConnection: " & error.code'image & " " & error.message );
  Print~>error( error );
  generate RemoteConnection.close() to this;

end state;

domain Socket is
  
  public type sockethandle is integer;   
  public type sockfamily is enum ( AF_INET );   
  public type data is sequence of byte;   
  public type socktype is enum ( SOCK_STREAM, SOCK_DGRAM );   
  public type sockproto is enum ( TCP, UDP );   
  public type optionlevel is enum ( SOL_SOCKET );   
  public type optionname is enum ( SO_DEBUG, SO_ACCEPTCONN, SO_BROADCAST, SO_REUSEADDR, SO_KEEPALIVE, SO_LINGER, SO_OOBINLINE, SO_SNDBUF, SO_RCVBUF, SO_ERROR, SO_TYPE, SO_DONTROUTE, SO_RCVLOWAT, SO_RCVTIMEO, SO_SNDLOWAT, SO_SNDTIMEO );   
  public type sockaddr is structure
    family: sockfamily;     
    data: data;     
  end structure;   
  
  public service accept ( socket: in sockethandle,
                          address: out sockaddr ) return integer;   
  public service bind ( socket: in sockethandle,
                        address: in sockaddr ) return integer;   
  public service connect ( socket: in sockethandle,
                           address: in sockaddr ) return integer;   
  public service getpeername ( socket: in sockethandle,
                               address: out sockaddr ) return integer;   
  public service getsockname ( socket: in sockethandle,
                               address: out sockaddr ) return integer;   
  public service getsockopt ( socket: in sockethandle,
                              level: in optionlevel,
                              option: in optionname,
                              option_value: out data ) return integer;   
  public service listen ( socket: in sockethandle,
                          backlog: in integer ) return integer;   
  public service recv ( socket: in sockethandle,
                        buffer: out data,
                        length: in integer,
                        flags: in integer ) return integer;   
  public service recvfrom ( socket: in sockethandle,
                            buffer: out data,
                            length: in integer,
                            flags: in integer,
                            address: out sockaddr ) return integer;   
  public service sendto ( socket: in sockethandle,
                          message: in data,
                          length: in integer,
                          flags: in integer,
                          address: in sockaddr ) return integer;   
  public service setsockopt ( socket: in sockethandle,
                              level: in optionlevel,
                              option: in optionname,
                              option_value: in data ) return integer;   
  public service send ( socket: in sockethandle,
                        message: in data,
                        length: in integer,
                        flags: in integer ) return integer;   
  public service shutdown ( socket: in sockethandle,
                            how: in integer ) return integer;   
  public service socket ( family: in sockfamily,
                          socktype: in socktype,
                          protocol: in sockproto ) return sockethandle;   
  
end domain;

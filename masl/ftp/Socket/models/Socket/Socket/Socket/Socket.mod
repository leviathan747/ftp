domain Socket is
  public type sockethandle is integer
  ;
  public type data is sequence of byte
  ;
  public type socktype is enum (SOCK_STREAM, SOCK_DGRAM)
  ;
  public type sockproto is enum (IPPROTO_TCP, IPPROTO_UDP)
  ;
  public type optionlevel is enum (SOL_SOCKET)
  ;
  public type optionname is enum (SO_DEBUG, SO_ACCEPTCONN, SO_BROADCAST, SO_REUSEADDR, SO_KEEPALIVE, SO_LINGER, SO_OOBINLINE, SO_SNDBUF, SO_RCVBUF, SO_ERROR, SO_TYPE, SO_DONTROUTE, SO_RCVLOWAT, SO_RCVTIMEO, SO_SNDLOWAT, SO_SNDTIMEO)
  ;
//!address is a string representation of an IPv4 address in the format
//!"<byte>.<byte>.<byte>.<byte>" where each byte is the ASCII representation
//!of a decimal integer.
//!
//!port is a 16 bit integer represented in decimal.
  public type sockaddr is structure
  address: string;
  port: integer;
end structure
  ;
    public service accept (
        socket : in sockethandle,        address : out sockaddr    ) return sockethandle;
    public service bind (
        socket : in sockethandle,        address : in sockaddr    ) return integer;
    public service connect (
        socket : in sockethandle,        address : in sockaddr    ) return integer;
    public service getpeername (
        socket : in sockethandle,        address : out sockaddr    ) return integer;
    public service getsockname (
        socket : in sockethandle,        address : out sockaddr    ) return integer;
    public service getsockopt (
        socket : in sockethandle,        option : in optionname,        value : out data    ) return integer;
    public service listen (
        socket : in sockethandle,        backlog : in integer    ) return integer;
    public service recv (
        socket : in sockethandle,        buffer : out data,        length : in integer,        flags : in integer    ) return integer;
    public service recvfrom (
        socket : in sockethandle,        buffer : out data,        length : in integer,        flags : in integer,        address : out sockaddr    ) return integer;
    public service sendto (
        socket : in sockethandle,        message : in data,        length : in integer,        flags : in integer,        address : in sockaddr    ) return integer;
    public service setsockopt (
        socket : in sockethandle,        option : in optionname,        value : in data    ) return integer;
    public service send (
        socket : in sockethandle,        message : in data,        length : in integer,        flags : in integer    ) return integer;
    public service shutdown (
        socket : in sockethandle,        how : in integer    ) return integer;
    public service socket (
        socktype : in socktype,        protocol : in sockproto    ) return sockethandle;
    private service testrecv (
    );
pragma test_only ( true ); pragma scenario ( 1 ); 
    private service testsend (
    );
pragma scenario ( 2 ); pragma test_only ( true ); 
    public service datatostring (
        data : in data    ) return string;
    public service errno (
    ) return integer;
    public service strerror (
        errno : in integer    ) return string;
    public service durationtotimeval (
        duration : in duration    ) return data;
    private service stringtodata (
        s : in string    ) return data;
end domain;

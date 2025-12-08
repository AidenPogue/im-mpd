#include <string>
#include <mpd/client.h>

class MpdClientWrapper
{
private:
    mpd_connection *connection;

    void ThrowIfNotConnected();

public:
    MpdClientWrapper(std::string hostname, uint port);
    ~MpdClientWrapper();

    mpd_song *GetCurrentSong();
};
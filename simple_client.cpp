#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>

#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/lazy_entry.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <boost/filesystem/operations.hpp>

int main(int argc, char* argv[])
{
        using namespace libtorrent;
#if BOOST_VERSION < 103400
        namespace fs = boost::filesystem;
        fs::path::default_name_check(fs::no_check);
#endif

if (argc != 2)
{
        std::cerr << "usage: ./sc torrent_file.torrent\n"
                "to stop the client, press return.\n";
        return 1;
}

#ifndef BOOST_NO_EXCEPTIONS
        try
#endif
        {
                session s;
                s.set_download_rate_limit( 128000 );
                s.listen_on(std::make_pair(6881, 6889));
                add_torrent_params p;
                p.save_path = "./";
                p.ti = new torrent_info(argv[1]);
                s.add_torrent(p);

                bool cont = true;
                while( cont ) {
                // wait for the user to end
                    session_status ss = s.status();
                    std::cout << "Session Stats:" << "\n";
                    std::cout << "\t Total Download:" << ss.total_download << " Total Upload:" << ss.total_upload << "\n";

                    std::vector<torrent_handle> v = s.get_torrents(); 
                    for(std::vector<int>::size_type i = 0; i != v.size(); i++) {
                        torrent_handle t = v[i];
                        std::cout << "Torrent " << t.name() << " Progress " << t.status().progress * 100 << "%" << "\n";
 
                        if( t.status().progress == 1.0 ) {
                            exit(0);
    
                        }
                    }
                    sleep( 1 );
                }
        }
#ifndef BOOST_NO_EXCEPTIONS
        catch (std::exception& e)
        {
                std::cout << e.what() << "\n";
        }
#endif
        return 0;
}

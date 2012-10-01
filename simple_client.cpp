#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>

#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/lazy_entry.hpp>
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
        std::cerr << "usage: ./simple_client torrent-file\n"
                "to stop the client, press return.\n";
        return 1;
}

#ifndef BOOST_NO_EXCEPTIONS
        try
#endif
        {
                session s;
                s.listen_on(std::make_pair(6881, 6889));
                add_torrent_params p;
                p.save_path = "./";
                p.ti = new torrent_info(argv[1]);
                s.add_torrent(p);

                // wait for the user to end
                char a;
                std::cin.unsetf(std::ios_base::skipws);
                std::cin >> a;
        }
#ifndef BOOST_NO_EXCEPTIONS
        catch (std::exception& e)
        {
                std::cout << e.what() << "\n";
        }
#endif
        return 0;
}

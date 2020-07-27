#include <Engine.h>
#include <GameState.h>
#include <cinttypes>
//#include <nn.h>
//#include <pipeline.h>
#include <asio.hpp>

#include "../Shared/Packet.h"
#include "EntityEditor.h"

class GS_Menu : public MMT::GameState
{
private:
	MMT::Button *Btn_Connect = nullptr, *Btn_Settings = nullptr, *Btn_Exit = nullptr;
	MMT::Image *Img_Splash = nullptr;
public:
	GS_Menu(MMT::Engine *Parent) :
		MMT::GameState(Parent, "Main Menu")
	{

	}

	void Init() override
	{

	}

	bool Load() override
	{
		auto WinSize = Parent->MainWindow.GetSize();

		Img_Splash = new MMT::Image(Parent, { static_cast<MMT::int32>(WinSize.h / 2) - 12, 1 }, { 23, 8 });
		Img_Splash->LoadFile("Vienes.xp");
		Widgets.push_back(Img_Splash);

		Btn_Connect = new MMT::Button(Parent, "Connect to Server", { static_cast<MMT::int32>((WinSize.h / 2)) - static_cast<MMT::int32>(strlen("Connect to Server") / 2), 11 }, [this](void*)
		{
			Parent->PushState(2);
		});
		Btn_Connect->Color.fg = MMT::Colors::LightGrey;
		Widgets.push_back(Btn_Connect);

		Btn_Settings = new MMT::Button(Parent, "Settings", { static_cast<MMT::int32>((WinSize.h / 2)) - static_cast<MMT::int32>(strlen("Settings") / 2), 14 }, [this](void*)
		{
			fmt::printf("Ed is a fuck\n");
		});
		Btn_Settings->Color.fg = MMT::Colors::LightGrey;
		Widgets.push_back(Btn_Settings);

		Btn_Exit = new MMT::Button(Parent, "Exit to Desktop", { static_cast<MMT::int32>((WinSize.h / 2)) - static_cast<MMT::int32>(strlen("Exit to Desktop") / 2), 17 }, [this](void*)
		{
			Parent->bStopRequested = true;
		});
		Btn_Exit->Color.fg = MMT::Colors::LightGrey;
		Widgets.push_back(Btn_Exit);

		//MMT::Sprite::

		return true;
	}

	void Cleanup() override
	{
		//delete Btn_Connect;
	}

	void Input() override
	{
		ProcessEvents();

		if (Parent->Keyboard[SDL_SCANCODE_F1] == 1u && Parent->Keyboard.Ctrl == 1u)
		{
			Parent->PushState(3);
		}
	}

	void Logic() override
	{

	}

	void Render(MMT::TileSurface &DrawScene) override
	{
		DrawScene.ClearSurface(MMT::Colors::Black);
		DrawWidgets();
	}
};

asio::error_code EC;
asio::io_service IOSvc;
asio::ip::tcp::resolver resolver(IOSvc);
asio::ip::tcp::resolver::query query("127.0.0.1", "8008");

class GS_Menu_Connect : public MMT::GameState
{
private:
	MMT::InputBox *Inp_IpAddress = nullptr;
	MMT::Label *Lbl_IPAddressBox = nullptr, *Lbl_ServerPing = nullptr;
	MMT::Button *Btn_Back = nullptr, *Btn_Ping = nullptr;
public:
	GS_Menu_Connect(MMT::Engine *Parent) :
		MMT::GameState(Parent, "Connection Menu")
	{

	}

	void Init() override
	{
		
	}

	bool Load() override
	{
		auto WinSize = Parent->MainWindow.GetSize();

		Inp_IpAddress = new MMT::InputBox(Parent, { (static_cast<MMT::int32>(WinSize.w) / 2) - 11, 11 }, "127.0.0.1:8008", 21);
		Inp_IpAddress->TextColor = MMT::Colors::LightGrey;
		Inp_IpAddress->BackgroundColor = MMT::Colors::DarkGrey;
		Inp_IpAddress->BackgroundMouseColor = MMT::Lerp(MMT::Colors::DarkGrey, MMT::Colors::Grey, 0.35);
		Widgets.push_back(Inp_IpAddress);

		Lbl_IPAddressBox = new MMT::Label(Parent, { (static_cast<MMT::int32>(WinSize.w) / 2) - (static_cast<MMT::int32>(strlen("IP Address")) / 2), 13 }, "IP Address", { MMT::Colors::Grey, MMT::Colors::Black });
		//Lbl_IPAddressBox->TextColor = { MMT::Colors::Grey, MMT::Colors::Black };
		Widgets.push_back(Lbl_IPAddressBox);

		Lbl_ServerPing = new MMT::Label(Parent, { (static_cast<MMT::int32>(WinSize.w) / 2) - (static_cast<MMT::int32>(strlen("-")) / 2), 20 }, "-", { MMT::Colors::Grey, MMT::Colors::Black });
		Widgets.push_back(Lbl_ServerPing);

		Btn_Ping = new MMT::Button(Parent, "Ping Server", { (static_cast<MMT::int32>(WinSize.w) / 2) - (static_cast<MMT::int32>(strlen("Ping Server")) / 2), 18 }, [this](void *PingLabel)
		{
			/*int socket = nn_socket(AF_SP, NN_PUSH);
			if (socket >= 0)
			{
				int sockid = nn_connect(socket, "tcp://127.0.0.1:8008");
				if (sockid >= 0)
				{
					Packet_ConnectRequest *Pkt = new Packet_ConnectRequest;
					Pkt->PublicAddress = 0x7F000001u;
					memset(Pkt->User, 0, sizeof(char) * 16);
					strcpy_s(Pkt->User, "USERNAME");
					Pkt->PassHash = XXH32("PASSWORD", strlen("PASSWORD"), 0);

					msgpack::sbuffer MsgPackBuffer;
					msgpack::packer<msgpack::sbuffer> MsgPackerPacker(&MsgPackBuffer);
					
					msgpack::adaptor::pack<Packet_ConnectRequest>()(MsgPackerPacker, *Pkt);

					int sendlen = nn_send(socket, MsgPackBuffer.data(), MsgPackBuffer.size(), 0);
					if (sendlen >= 0)
					{
						printf("Packet type: %" PRIu8 "\n", Pkt->Type);
						printf("Sent %d bytes.\n", sendlen);
					}
					delete Pkt;
				}
			}*/
			asio::ip::tcp::resolver::iterator iter = resolver.resolve(query, EC);
			asio::ip::tcp::resolver::iterator end;
			if (!EC)
			{
				while (iter != end)
				{
					asio::ip::tcp::socket sock(IOSvc);

					// Start the timer
					MMT::uint32 Time = SDL_GetTicks();

					sock.connect(iter->endpoint(), EC);
					if (!EC)
					{
						std::string tbuf = "fishyblublub";
						size_t sent = asio::write(sock, asio::buffer(tbuf));
						//size_t sent = sock.write_some(asio::buffer(tbuf), EC);
						if (!EC)
						{
							char buffer[256];
							memset(buffer, 0, sizeof(buffer));
							//size_t bytes = asio::read(sock, asio::buffer(buffer), EC);
							size_t bytes = sock.receive(asio::buffer(buffer), 0, EC);
							
							if (!EC)
							{
								Time = SDL_GetTicks() - Time;
								fmt::print("Sent {} bytes to {}:{}\n", sent, iter->endpoint().address().to_string(), iter->endpoint().port());
								fmt::print("Recieved a {}-byte reply: '{}'.\n", bytes, buffer);
								fmt::print("Round-trip time: {}ms\n", Time);

								// Re-center and update ping box
								std::string pingString = fmt::format("{0}ms", Time);
								MMT::Label *lblPing = static_cast<MMT::Label*>(PingLabel);

								lblPing->BoundingBox.x = (static_cast<MMT::int32>(Parent->MainWindow.GetSize().w) / 2) - (static_cast<MMT::int32>(pingString.length()) / 2);
								lblPing->BoundingBox.w = pingString.length();
								lblPing->Text = pingString;
							}
							else
							{
								fmt::print("ERROR: {}\n", EC.message());
							}
						}
						else
						{
							fmt::print("ERROR: {}\n", EC.message());
						}
						sock.shutdown(asio::ip::tcp::socket::shutdown_both);
						sock.close();
					}
					else
					{
						fmt::print("ERROR: {}\n", EC.message());
					}
					iter++;
				}
			}
			else
			{
				fmt::print("ERROR: {}\n", EC.message());
			}
		}, Lbl_ServerPing);
		Btn_Ping->Color.fg = MMT::Colors::LightGrey;
		Widgets.push_back(Btn_Ping);

		Btn_Back = new MMT::Button(Parent, "Back", { (static_cast<MMT::int32>(WinSize.w) / 2) - 2, 26 }, [this](void*)
		{
			Parent->PopState();
		});
		Btn_Back->Color.fg = MMT::Colors::LightGrey;
		Widgets.push_back(Btn_Back);

		return true;
	}

	void Cleanup() override
	{
		//delete Btn_Connect;
	}

	void Input() override
	{
		ProcessEvents();
	}

	void Logic() override
	{

	}

	void Render(MMT::TileSurface &DrawScene) override
	{
		DrawScene.ClearSurface(MMT::Colors::Black);
		DrawWidgets();
	}
};

#define GAME_TITLE		"Vienes"
#define GAME_VERSION	"alpha 0.0.1"

int main(int argc, char *argv[])
{
	MMT::Initialize();              
	MMT::Engine Engine(GAME_TITLE " : " GAME_VERSION);
	Engine.RegisterState(1, new GS_Menu(&Engine));
	Engine.RegisterState(2, new GS_Menu_Connect(&Engine));
	Engine.RegisterState(3, new GS_EntityEditor(&Engine));
	Engine.PushState(1);
	Engine.Initialize({ 30, 30 }, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
	Engine.Run();

	MMT::Exit();
	return 0;
}
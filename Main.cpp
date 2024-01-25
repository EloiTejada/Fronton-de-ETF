#include "fronton.h"
#include <sstream>

using namespace std;
bool paused = true;

int main() {
        //Finestra
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();                                                                                    //Variable per obtenir la mida de la teva pantalla

    
    unsigned int screenWidth = desktopMode.width;                                                                                                   //Variable que amagatzema la amplada de la pantalla.
    unsigned int screenHeight = desktopMode.height;                                                                                                 //Variable que amagatzema la altura de la pantalla.
    Vector2f viewSize(screenWidth, screenHeight);                                                                                                   //Vector que ens ser� util per configurar la mida de la finestra.
    VideoMode vm(viewSize.x, viewSize.y);                                                                                                           //Variable que asigna la amplada i mida de la finesta.
    RenderWindow window(vm, title, Style::Default);                                                                                                 //Variable que crea la finesta, aix� com li dona un t�tol i una font.
    window.setFramerateLimit(60);                                                                                                                   //Limitem el r�tio de frames.
    
    


    
    int radi = ((screenHeight + screenWidth) / 100) * 1;                                                                                            //Variable que li dona mida a la nostra pilota.
    CircleShape bola(radi);                                                                                                                         //Definim la variable de la pilota i li assignem la mida.
    bola.setFillColor(Color::White);                                                                                                                //Li donem un color.
    bola.setOrigin(bola.getRadius(), bola.getRadius());                                                                                             //Li assignem un origen.
    bola.setPosition(viewSize.x / 2, viewSize.y / 2);                                                                                               //Li donem una posici� inicial.


    
    float ballSpeedY = ballSpeedBase * 1, ballSpeedX = ballSpeedBase * 1.7;                                                                         //Variables per la velocitat de la bola.

    RectangleShape player;                                                                                                                          //Definim el rectangle que ser� el jugador.

    player.setFillColor(Color::White);                                                                                                              //Li donem un color.
    player.setSize(Vector2f(longitut, amplada));                                                                                                    //Li donem una mida.
                            
    FloatRect playerRect = player.getLocalBounds();                                                                                                 //Definim una variable FLOATRECT que amagatzemar� la HitBox del jugador.
    player.setOrigin(playerRect.left + playerRect.width / 2.0f, playerRect.top + playerRect.height / 2.0f);                                         //Li donem un origen.
    player.setPosition(viewSize.x / 2, viewSize.y - 50);                                                                                            //Li assignem la posici� inicial.

    struct Bloc {                                                                                                                                   //Definim una estructura pels blocs que crearem
        bool active = true;                                                                                                                         //Cont� una booleana
        Sprite spriteBloc;                                                                                                                          //I un sprite

    };

    Texture textureBlocs;                                                                                                                           //Creem una variable Texture per als nostres blocs.
    textureBlocs.loadFromFile("Recursos/Bloc.png");                                                                                                 //Li assingem una textura a la nostra variable.
    Bloc spriteBlocs[NumMaxBlocs];                                                                                                                  //Definim els nostres sprites com a un array.
    for (int i = 0; i < NumMaxBlocs; ++i) {                                                                                                         //Funci� per crear tants sprites com desitgis i els hi dona un tamany.
        spriteBlocs[i].spriteBloc.setScale(0.5, 0.5);
    }
    
    Font font;                                                                                                                                      //Definim una variable del tipus Font.
    Text timeElapsed;                                                                                                                               //Definim una variable del tipus Text.
    timeElapsed.setCharacterSize(24);                                                                                                               //Assinga un tamany als car�cters.

   
    

    Clock clock;                                                                                                                                    //Variable del tipus Clock

    while (window.isOpen()) {                                                                                                                       //Mentres la finestra estigui oberta:
       
        if (paused == true) {                                                                                                                       //Variable que hauria de pausar el joc abans de comen�ar i ser t� el que 
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {                                                                                          //elegeix quan comen�a, pero no s� perqu�, no funciona.
                paused == false;
            }

        }
        do {                                                                                                                                        //Tamb� t� que veure amb la booleana paused, que no funciona.
            if (Keyboard::isKeyPressed(Keyboard::Return)) {                                                                                         //Si prems la tecla Return, tenca la finestra(en veritat el Return no funciona,
            window.close();                                                                                                                         // nom�s tenca si prems Enter, curi�s...
        }
                                                                                                                 
            float elapsedTime = clock.getElapsedTime().asSeconds();                                                                                 //Variable que amagatzema el temps.

            ostringstream ss;                                                                                                                       //Variables per amagatzemar un String que va variant en una variable.
            ss << "Time: " << elapsedTime;                                                                                                          
            timeElapsed.setString(ss.str());
            timeElapsed.setPosition(viewSize.x/ 2.0f, viewSize.y / 2.0f);                                                                           //Li donem una posici� inical.

            
            // Update input

            if (Keyboard::isKeyPressed(Keyboard::Right)) {                                                                                          //Si prems la tecla dreta, el player es mou a la dreta
                player.move(45, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {                                                                                          //Si prems la tecla esquerra, el player es mou a la esquerra
                player.move(-45, 0);
            }

            bola.move(ballSpeedX, ballSpeedY);                                                                                                      //Fem que la bola es mogui.
            if (bola.getGlobalBounds().intersects(player.getGlobalBounds())) {                                                                      //Si la pilota toca al jugador:

                ballSpeedX = -ballSpeedX * -1.0f;                                                                                                   //Canvia de direcc��
                ballSpeedY = -ballSpeedY * 1.0f;
            }
            for (int i = 0; i < NumMaxBlocs; ++i) {
                if (bola.getGlobalBounds().intersects(spriteBlocs[i].spriteBloc.getGlobalBounds()) && bola.getPosition().y < window.getSize().y / 10) { //Si la bola toca els blocs estant per sota de aquests:

                    ballSpeedX = ballSpeedX * -1.0f;                                                                                                //Rebota en una certa direcci�
                    ballSpeedY = ballSpeedY * 1.0f;
                    spriteBlocs[i].active = false;                                                                                                  //Eliminem aquell bloc
                    spriteBlocs[i].spriteBloc.setPosition(2000, 2000);                                                                              //El moguem a prendre pel sac.
                    
                }
                else if (bola.getGlobalBounds().intersects(spriteBlocs[i].spriteBloc.getGlobalBounds()) && bola.getPosition().y > window.getSize().y / 10) { //Si, en canvi, toca els blocs pel costat.
                        
                    ballSpeedX = ballSpeedX * 1.0f;                                                                                                 //Rebota en un altra direcci�.
                    ballSpeedY = ballSpeedY * -1.0f;
                    spriteBlocs[i].active = false;
                    spriteBlocs[i].spriteBloc.setPosition(2000, 2000);                                                                              //Tamb� s'en van a fregir castanyes.
                    
                }


            }
            if (bola.getPosition().x <= 0 || bola.getPosition().x + bola.getGlobalBounds().width >= window.getSize().x) {                           //Si la bola toca els cantons de la finestra, rebota.

                ballSpeedX = -ballSpeedX * 1.0f;
            }
            if (bola.getPosition().y <= 0 || bola.getPosition().y + bola.getGlobalBounds().width >= window.getSize().y) {

                ballSpeedY = -ballSpeedY * 1.0f;
            }


            for (int i = 0; i < NumMaxBlocs; ++i) {                                                                                                  //Aqui definim la posici� dels blocs
                if (spriteBlocs[i].active == true) {
                    spriteBlocs[i].spriteBloc.setTexture(textureBlocs);
                    float separaci� = 150 * i;
                    spriteBlocs[i].spriteBloc.setPosition((window.getSize().x / 10) + separaci�, window.getSize().y / 100);
                }
            }
        } while (paused == false); 
        
        window.clear(Color::Black);                                                                                                                  //Buidem la pentalla i hi posem un fons negre.
        window.draw(bola);                                                                                                                           //Dibuixem totes les notres variables.
        window.draw(player);
        for (int i=0; i<NumMaxBlocs; i++)
        window.draw(spriteBlocs[i].spriteBloc);
        window.draw(timeElapsed);
        window.display();                                                                                                                            //Ho mostrem a la finestra.
    }
    return 0;
}



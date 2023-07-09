#include "mygrid.h"

//constructor
MyGrid::MyGrid(QWidget *parent): QGridLayout() {
    //initizalize variables
    score = 0;
    remaining = 50;
    flippedC = nullptr; //the card flipped if there is one
    animals = {"panda", "duck", "lion", "tiger", "elephant",
                           "giraffe", "monkey", "zebra", "kangaroo", "penguin",
                           "dolphin", "koala", "horse", "dog", "cat", "bird"};
    stop=0; //Used when 2 cards are flipped >> the game will continue to take input but won’t use it. (check flip func)
    sample_palette.setColor(QPalette::Window, Qt::white);
    //available array initilizaing
    for(int i = 0; i < 15; i++) {
        this->avliable[i] = 2;
    }
}

QString MyGrid::random_name_generator() {
    int randomNumber =  QRandomGenerator::global()->bounded(0, 15);
    while(avliable[randomNumber] == 0) { //if the name is already used twice, choose another name
        randomNumber =  QRandomGenerator::global()->bounded(0, 15);
    }
    --avliable[randomNumber];
    return animals[randomNumber];
}

void MyGrid::flip_card(mycard *card) {
    //handles unnecessary input
    // e.g. pushing a button that is already flipped or out of the game ,or there are another already 2 flipped cards.
    if(card->out == 1 || card->flipped == 1 ||stop==1) {
        return;
    }
    //checks if  there is a flipped card or not, and do what it is supposed to do.
    // flippedC is the card object flipped is an attribute of mycard class
    else {
        if(flippedC == nullptr) {
            flippedC = card;
            card->setText(card->objectName());
            card->flipped=1;
        } else {
            card->setText(card->objectName());
            stop=1;
            // WAIT,
            //Note: this whole block waits for 1 sec but the code doesn't, the program keeps taking input
            //(handled these unnecessary inputs in the first if-else)
            QTimer::singleShot(1000, [this, card]() {
                if(card->objectName() == flippedC->objectName()) {
                    score += 1;

                    //changes score text
                    scoreL->setText(QString::number(this->score));
                    card->out=1;
                    flippedC->out=1;
                    card->setText(" ");
                    flippedC->setText(" ");
                    //creates a message box and stops the game till new game pressed
                    if(score==15){
                        QMessageBox msgBox;
                        msgBox.setText("You won!");
                        msgBox.exec();
                        msgBox.setStandardButtons(QMessageBox::Cancel);
                        return;
                    }
                } else {
                    card->setText("?");
                    flippedC->setText("?");
                }
                card->flipped=0;
                flippedC->flipped=0;
                flippedC = nullptr;
                stop=0;
                remaining--;
                triesL->setText(QString::number(this->remaining)); //changes tries text
                if(remaining==0){
                    QMessageBox msgBox;
                    msgBox.setText("You lost!");
                    msgBox.exec();
                    msgBox.setStandardButtons(QMessageBox::Cancel);
                    stop=1;
                    return;
                }

            });
        }
    }
}


void MyGrid::create_grid() {
    //Note: to convert int to string, use  QString::number(this->score)
    scoreL = new QLabel(QString::number(this->score));
    scoreL->setAlignment(Qt::AlignCenter);
    scoreL->setAutoFillBackground(true);
    scoreL->setPalette(sample_palette);

    triesL = new QLabel(QString::number(this->remaining));
    triesL->setAlignment(Qt::AlignCenter);
    triesL->setAutoFillBackground(true);
    triesL->setPalette(sample_palette);

    QLabel *label1 = new QLabel("Score");//this is not going to change
    label1->setAlignment(Qt::AlignCenter);
    label1->setAutoFillBackground(true);
    label1->setPalette(sample_palette);

    //same just <br> means new line like html
    QLabel *label2 = new QLabel("No. of Tries <br> Remaining");
    label2->setAlignment(Qt::AlignCenter);
    label2->setAutoFillBackground(true);
    label2->setPalette(sample_palette);

    this->addWidget(label1,0,0,1,1); // addWidget(wName,row,column,how many rows it will take,same for column)
    this->addWidget(scoreL,0,1,1,1);
    this->addWidget(label2,0,2,1,1);
    this->addWidget(triesL,0,3,1,1);
    this->setSpacing(2);//allings spacing inside grid

    //(lambda func)
    QPushButton *newGame= new QPushButton("New Game");
    QObject::connect(newGame, &QPushButton::clicked, [this]() {
        this->score=0;//sets score zero and stuff
        this->stop=0;
        this->remaining=50;
        for(int i = 0; i < 15; i++) {
            avliable[i] = 2;
        }
        //in the array makes each card goes to beginning
        for(int i=0;i<30;i++){
            arr[i]->setText("?");//changes what user sees
            arr[i]->setObjectName(random_name_generator());
            arr[i]->flipped=0;
            arr[i]->out=0;
        }
        //changes what user sees
        scoreL->setText(QString::number(this->score));
        triesL->setText(QString::number(this->remaining));
    });

    QPalette pal = QPalette();
    pal.setColor(QPalette::Button, QColor(QColorConstants::Svg::lightsteelblue));
    newGame->setFlat(true);
    newGame->setAutoFillBackground(true);
    newGame->setPalette(pal);
//    update();//requires repainting

    this->addWidget(newGame,0,4,1,2);//alligning the button made it take two column
    QLabel *label3 = new QLabel(" ");// white area btw cards and upper part
    label3->setAlignment(Qt::AlignCenter);
    label3->setAutoFillBackground(true);
    label3->setPalette(sample_palette);
    this->addWidget(label3,1,0,1,6);

    //this part initialize and adds all the buttons.
    int i=0;
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 6; col++) {
            mycard *randButton = new mycard("?");
            randButton->setObjectName(random_name_generator());
            arr[i]=randButton;
            //this part i send it to flip card func when it is pushed
            QObject::connect(randButton, &mycard::clicked, [this, randButton]() {
                flip_card(randButton);
            });
            //adding it to widget
            this->addWidget(randButton, row+2, col, 1, 1);
            i++;
        }
    }



}

#include "MainWindow.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Tiro con Arco");
    setFixedSize(900, 600);

    nivelNumero   = 1;
    flechaEnVuelo = false;
    juegoActivo   = true;
    anguloActual  = 45.0f;
    fuerzaActual  = 15.0f;
    flechaActual  = nullptr;
    lineaFlecha   = nullptr;
    puntaFlecha   = nullptr;

    // Widget central
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(central);
    layoutPrincipal->setSpacing(0);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);

    // Panel de info arriba
    QWidget* panelInfo = new QWidget(central);
    panelInfo->setFixedHeight(40);
    panelInfo->setStyleSheet("background-color: #1a1a2e;");
    QHBoxLayout* layoutInfo = new QHBoxLayout(panelInfo);

    labelInfo    = new QLabel("Nivel 1 — Usa W/S para ángulo, A/D para fuerza, ESPACIO para disparar", panelInfo);
    labelAngulo  = new QLabel("Ángulo: 45°", panelInfo);
    labelFuerza  = new QLabel("Fuerza: 15", panelInfo);

    labelInfo->setStyleSheet("color: white; font-size: 11px;");
    labelAngulo->setStyleSheet("color: #00ff88; font-size: 12px; font-weight: bold;");
    labelFuerza->setStyleSheet("color: #ffaa00; font-size: 12px; font-weight: bold;");

    layoutInfo->addWidget(labelInfo);
    layoutInfo->addStretch();
    layoutInfo->addWidget(labelAngulo);
    layoutInfo->addSpacing(20);
    layoutInfo->addWidget(labelFuerza);

    // Escena y vista
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 900, 540);

    vista = new QGraphicsView(escena, central);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFixedSize(900, 540);

    layoutPrincipal->addWidget(panelInfo);
    layoutPrincipal->addWidget(vista);

    // Jugador y nivel
    jugador = new Jugador();
    jugador->setAngulo(anguloActual);
    jugador->setFuerza(fuerzaActual);

    configurarNivel1();

    // Timer del juego — 60fps aprox
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    timer->start(16);

    setFocus();
}

MainWindow::~MainWindow()
{
    delete jugador;
    delete nivelActual;
    if (flechaActual != nullptr)
        delete flechaActual;
}

void MainWindow::configurarNivel1()
{
    escena->clear();
    lineaFlecha = nullptr;
    puntaFlecha = nullptr;

    if (flechaActual != nullptr)
    {
        delete flechaActual;
        flechaActual = nullptr;
    }

    flechaEnVuelo = false;
    nivelNumero   = 1;

    nivelActual = new Nivel(1, 2);
    nivelActual->agregarObjetivo(0, new ObjetivoFijo(650.0f, 250.0f, 35.0f));
    nivelActual->agregarObjetivo(1, new ObjetivoFijo(750.0f, 380.0f, 35.0f));

    dibujarFondo();
    dibujarArco();
    dibujarObjetivos();

    labelInfo->setText("Nivel 1 — W/S: ángulo | A/D: fuerza | ESPACIO: disparar");
}

void MainWindow::configurarNivel2()
{
    escena->clear();
    lineaFlecha = nullptr;
    puntaFlecha = nullptr;

    if (flechaActual != nullptr)
    {
        delete flechaActual;
        flechaActual = nullptr;
    }

    flechaEnVuelo = false;
    nivelNumero   = 2;

    nivelActual = new Nivel(2, 2);
    nivelActual->agregarObjetivo(0, new ObjetivoMovil(550.0f, 200.0f, 30.0f, 80.0f, 400.0f, 750.0f));
    nivelActual->agregarObjetivo(1, new ObjetivoMovil(700.0f, 360.0f, 30.0f, 60.0f, 500.0f, 820.0f));
    nivelActual->agregarPortal(new Portal(300.0f, 300.0f, 600.0f, 150.0f, 35.0f));

    dibujarFondo();
    dibujarArco();
    dibujarObjetivos();
    dibujarPortal();

    labelInfo->setText("Nivel 2 — Dianas en movimiento. El portal teletransporta la flecha.");
}

void MainWindow::dibujarFondo()
{
    // Cielo
    QGraphicsRectItem* cielo = escena->addRect(0, 0, 900, 400);
    cielo->setBrush(QBrush(QColor(135, 206, 235)));
    cielo->setPen(Qt::NoPen);

    // Nubes simples
    for (int i = 0; i < 3; i++)
    {
        int cx = 150 + i * 280;
        QGraphicsEllipseItem* n1 = escena->addEllipse(cx,      60, 80, 40);
        QGraphicsEllipseItem* n2 = escena->addEllipse(cx + 40, 50, 90, 45);
        QGraphicsEllipseItem* n3 = escena->addEllipse(cx + 80, 60, 70, 38);
        n1->setBrush(Qt::white); n1->setPen(Qt::NoPen);
        n2->setBrush(Qt::white); n2->setPen(Qt::NoPen);
        n3->setBrush(Qt::white); n3->setPen(Qt::NoPen);
    }

    // Pasto
    QGraphicsRectItem* pasto = escena->addRect(0, 400, 900, 140);
    pasto->setBrush(QBrush(QColor(34, 139, 34)));
    pasto->setPen(Qt::NoPen);

    // Línea del suelo
    QGraphicsLineItem* suelo = escena->addLine(0, 400, 900, 400);
    suelo->setPen(QPen(QColor(0, 100, 0), 2));
}

void MainWindow::dibujarArco()
{
    // Base del arquero
    QGraphicsRectItem* base = escena->addRect(60, 330, 30, 70);
    base->setBrush(QBrush(QColor(80, 50, 20)));
    base->setPen(Qt::NoPen);

    // Arco (curva)
    QPainterPath arco;
    arco.moveTo(75, 290);
    arco.cubicTo(30, 330, 30, 380, 75, 410);
    QGraphicsPathItem* itemArco = escena->addPath(arco);
    itemArco->setPen(QPen(QColor(101, 67, 33), 5));

    // Cuerda
    QGraphicsLineItem* cuerda = escena->addLine(75, 290, 75, 410);
    cuerda->setPen(QPen(QColor(200, 200, 180), 1));
}

void MainWindow::dibujarFlecha()
{
    if (lineaFlecha != nullptr)
    {
        escena->removeItem(lineaFlecha);
        delete lineaFlecha;
        lineaFlecha = nullptr;
    }
    if (puntaFlecha != nullptr)
    {
        escena->removeItem(puntaFlecha);
        delete puntaFlecha;
        puntaFlecha = nullptr;
    }

    if (flechaActual == nullptr) return;

    float fx = flechaActual->getX();
    float fy = flechaActual->getY();

    // Convertir coordenadas lógicas a pantalla
    // El arco está en x=75, y=350 en pantalla
    // La escena tiene y=0 arriba, pero la física tiene y=0 abajo
    float px = 75.0f + fx;
    float py = 350.0f - fy;

    // Cuerpo de la flecha
    float largo = 28.0f;
    float rad   = anguloActual * 3.1416f / 180.0f;
    float dx    = std::cos(rad) * largo;
    float dy    = -std::sin(rad) * largo;

    lineaFlecha = escena->addLine(px - dx, py - dy, px, py);
    lineaFlecha->setPen(QPen(QColor(139, 90, 43), 3));

    // Punta triangular
    QPolygonF punta;
    punta << QPointF(px, py)
          << QPointF(px - dx * 0.4f + dy * 0.15f, py - dy * 0.4f + dx * 0.15f)
          << QPointF(px - dx * 0.4f - dy * 0.15f, py - dy * 0.4f - dx * 0.15f);

    puntaFlecha = escena->addPolygon(punta);
    puntaFlecha->setBrush(QBrush(QColor(180, 140, 60)));
    puntaFlecha->setPen(Qt::NoPen);
}

void MainWindow::dibujarObjetivos()
{
    // Las dianas las dibuja actualizarJuego cada frame
}

void MainWindow::dibujarPortal()
{
    // El portal lo dibuja actualizarJuego
}

void MainWindow::actualizarJuego()
{
    if (!juegoActivo) return;

    escena->clear();
    lineaFlecha = nullptr;
    puntaFlecha = nullptr;

    dibujarFondo();
    dibujarArco();

    // Dibujar objetivos
    for (int i = 0; i < nivelActual->getTotalObjetivos(); i++)
    {
        Objetivo* obj = nivelActual->getObjetivo(i);
        if (obj == nullptr) continue;

        float ox = 75.0f + obj->getX();
        float oy = 350.0f - obj->getY();

        if (obj->fueGolpeado())
        {
            // Diana acertada — se ve gris
            QGraphicsEllipseItem* e = escena->addEllipse(ox - 35, oy - 35, 70, 70);
            e->setBrush(QBrush(QColor(100, 100, 100)));
            e->setPen(Qt::NoPen);
            continue;
        }

        // Círculos de la diana
        QColor colores[] = {
            QColor(220, 20, 20),
            QColor(255, 255, 255),
            QColor(220, 20, 20),
            QColor(255, 255, 0)
        };
        int radios[] = {35, 25, 16, 8};

        for (int r = 0; r < 4; r++)
        {
            QGraphicsEllipseItem* circulo = escena->addEllipse(
                ox - radios[r], oy - radios[r],
                radios[r] * 2, radios[r] * 2
                );
            circulo->setBrush(QBrush(colores[r]));
            circulo->setPen(QPen(QColor(50, 50, 50), 1));
        }
    }

    // Portal (nivel 2)
    if (nivelNumero == 2 && nivelActual->getPortal() != nullptr)
    {
        Portal* p = nivelActual->getPortal();
        float px1 = 75.0f + p->getEntradaX();
        float py1 = 350.0f - p->getEntradaY();
        float px2 = 75.0f + p->getSalidaX();
        float py2 = 350.0f - p->getSalidaY();

        // Portal entrada — azul
        for (int r = 3; r >= 0; r--)
        {
            int radio = 18 + r * 6;
            int alpha = 80 + r * 40;
            QGraphicsEllipseItem* anillo = escena->addEllipse(
                px1 - radio, py1 - radio, radio * 2, radio * 2
                );
            anillo->setBrush(Qt::NoBrush);
            anillo->setPen(QPen(QColor(50, 100, 255, alpha), 3));
        }
        QGraphicsEllipseItem* centroE = escena->addEllipse(px1 - 10, py1 - 10, 20, 20);
        centroE->setBrush(QBrush(QColor(100, 150, 255, 180)));
        centroE->setPen(Qt::NoPen);

        // Portal salida — naranja
        for (int r = 3; r >= 0; r--)
        {
            int radio = 18 + r * 6;
            int alpha = 80 + r * 40;
            QGraphicsEllipseItem* anillo = escena->addEllipse(
                px2 - radio, py2 - radio, radio * 2, radio * 2
                );
            anillo->setBrush(Qt::NoBrush);
            anillo->setPen(QPen(QColor(255, 140, 0, alpha), 3));
        }
        QGraphicsEllipseItem* centroS = escena->addEllipse(px2 - 10, py2 - 10, 20, 20);
        centroS->setBrush(QBrush(QColor(255, 180, 50, 180)));
        centroS->setPen(Qt::NoPen);
    }

    // Actualizar flecha en vuelo
    if (flechaEnVuelo && flechaActual != nullptr)
    {
        float dt = 0.016f;
        flechaActual->actualizar(dt);
        flechaActual->aplicarGravedad();

        float fx = flechaActual->getX();
        float fy = flechaActual->getY();

        // Verificar colisión con objetivos
        nivelActual->actualizar(dt, fx, fy);

        // Verificar portal
        if (nivelNumero == 2 && nivelActual->getPortal() != nullptr)
        {
            Portal* p = nivelActual->getPortal();
            if (p->detectarFlecha(flechaActual))
            {
                p->teletransportar(flechaActual);
            }
        }

        // Si sale de pantalla, se pierde
        float px = 75.0f + fx;
        float py = 350.0f - fy;

        if (px > 900 || py > 540 || py < 0 || px < 0)
        {
            delete flechaActual;
            flechaActual  = nullptr;
            flechaEnVuelo = false;
        }
        else
        {
            dibujarFlecha();
        }

        verificarNivelCompleto();
    }

    actualizarUI();
}

void MainWindow::verificarNivelCompleto()
{
    if (nivelActual->estaCompletado())
    {
        if (nivelNumero == 1)
        {
            delete nivelActual;
            nivelActual = nullptr;
            configurarNivel2();
        }
        else
        {
            juegoActivo = false;
            timer->stop();
            QGraphicsTextItem* txt = escena->addText("¡Juego completado!");
            txt->setDefaultTextColor(Qt::white);
            txt->setFont(QFont("Arial", 32, QFont::Bold));
            txt->setPos(250, 220);
        }
    }
}

void MainWindow::actualizarUI()
{
    labelAngulo->setText(QString("Ángulo: %1°").arg((int)anguloActual));
    labelFuerza->setText(QString("Fuerza: %1").arg((int)fuerzaActual));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!juegoActivo) return;

    switch (event->key())
    {
    case Qt::Key_W:
        if (anguloActual < 85.0f) anguloActual += 2.0f;
        break;

    case Qt::Key_S:
        if (anguloActual > 5.0f) anguloActual -= 2.0f;
        break;

    case Qt::Key_A:
        if (fuerzaActual > 5.0f) fuerzaActual -= 1.0f;
        break;

    case Qt::Key_D:
        if (fuerzaActual < 30.0f) fuerzaActual += 1.0f;
        break;

    case Qt::Key_Space:
        if (!flechaEnVuelo)
        {
            try
            {
                if (fuerzaActual <= 0)
                    throw std::invalid_argument("La fuerza no puede ser cero");

                jugador->setAngulo(anguloActual);
                jugador->setFuerza(fuerzaActual);

                if (flechaActual != nullptr)
                    delete flechaActual;

                flechaActual  = jugador->disparar();
                flechaEnVuelo = true;
            }
            catch (std::exception& e)
            {
                labelInfo->setText(QString("Error: ") + e.what());
            }
        }
        break;

    default:
        break;
    }

    jugador->setAngulo(anguloActual);
    jugador->setFuerza(fuerzaActual);
}

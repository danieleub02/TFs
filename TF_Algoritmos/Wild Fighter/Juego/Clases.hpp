#pragma once
using namespace::System; 
using namespace::System::Drawing;

ref class CObjeto
{
public:
	CObjeto(Bitmap^ img, Int16 nroF, Int16 nroC) {
		y = x = 0;
		sprite = img;
		nroFil = nroF;
		nroCol = nroC;
		ancho = sprite->Width / nroCol;
		alto = sprite->Height / nroFil;
		idCol = idFil = 0;
		animacion = false;
	}

	~CObjeto() {}

	Rectangle getRectangle() {
		return Rectangle(x, y, ancho, alto);
	}

	Void graficar(Graphics^ canvas) {
		Rectangle aVisible = Rectangle(idCol * ancho, idFil * alto, ancho, alto);
		canvas->DrawImage(sprite, x, y, aVisible, GraphicsUnit::Pixel);
	}

protected:
	Int16 x, y, idFil, idCol, nroFil, nroCol;
	Int32 ancho, alto;
	Bitmap^ sprite;
	Boolean animacion;
};


ref class Jugador : public CObjeto
{
public:
	Jugador(Bitmap^ img, int nF, int nC) :CObjeto(img, nF, nC) { x = 70; y = 230; vidas = 2010; }
	~Jugador() {}

	void gif() {
		if (animacion == true) {
			if (++idCol == 9) { idCol = 6; }
		}
	}

	void animar() {
		animacion = true;
		idFil = 0;
	};
	void parar() {
		animacion = false;
		idCol = 0;
	};
	void salto() {
		idFil = 4;
	};

	Boolean colisionar2(Rectangle Dino) {
		Rectangle rjugador = getRectangle();
		return rjugador.IntersectsWith(Dino);
	}
	Int16 mostrarcolision(Rectangle renemigo) {
		if (colisionar2(renemigo)) {
			vidas = vidas - 5;
		}
		return vidas;
	}
	Void mostrarLineaVida(Graphics^ lienzo) {
		lienzo->FillRectangle(Brushes::Blue, Rectangle(10, 10, 150, 30));
		lienzo->DrawString("Vidas: " + (vidas-10), gcnew System::Drawing::Font("Arial", 18), Brushes::White, 20, 10);

	}
private:
	Int16 vidas;

};

ref class Nativo : public CObjeto
{
public:
	Nativo(Bitmap^ img, int nF, int nC) :CObjeto(img, nF, nC) { y = 230; }
	~Nativo() {}


};

ref class Dino : public CObjeto
{
public:
	Dino(Bitmap^ img, int nF, int nC) :CObjeto(img, nF, nC) { x = 600; y = 230; };
	~Dino() {};

	void gif() {
		if (animacion == true) {
			if (++idCol == 9) { idCol = 6; }
		}
	}

	void animar() {
		animacion = true;
		idFil = 0;
	};
	void parar() {
		animacion = false;
		idCol = 0;
	};

	Void moverAutonomo() {
		x = x -15;
	}
};

ref class Escenario : public CObjeto
{
private:
	Int32 posVer;
	Int32 posHor;
public:
	Escenario(Bitmap^ img) :CObjeto(img, 1, 1) { y = -2700; posHor = 0; }
	~Escenario() {}

	Void mover(Int16 v) {
		switch (v) {
		case 0:x -= 7; break;
		case 1:x += 7; if (x > 0) { x = 0; }; break;
		}
	}

	Void vertical() {
		posVer = -(posHor * posHor) + 169;
		posHor = posHor + 1;
		y = y + posVer;
		if (posHor >= 23) {
			y = -2700;
			posHor = 23;
		}
	}

	Void caida() {
		y = -2700;
		posHor = posVer = 0;
	}

private:

};

ref class Tiempo {
private:
	Int32 contrareloj;

public:
	Tiempo() { contrareloj = 1; };
	~Tiempo() {};

	Void Cuenta(Graphics^ lienzo) {
		if (contrareloj == 1) {
			Console::WriteLine("Segundos transcurridos: ");
		}
		contrareloj++;
		Console::WriteLine(contrareloj);
	}

	Boolean Verifica(Graphics^ lienzo) {
		if (contrareloj == 30) {
			return true;
		}
	}

};

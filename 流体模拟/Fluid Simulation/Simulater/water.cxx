#define vtkRenderingCore_AUTOINIT 2(vtkRenderingOpenGL2, vtkInteractionStyle)
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "string"
#include"iostream"
#include "stdio.h"
#include <vtkBMPWriter.h>
#include <vtkBMPReader.h>
#include <vtkWindowToImageFilter.h>
#include <io.h>
#define allnumber 11
using namespace std;
vtkSphereSource **cone;
vtkPolyDataMapper **coneMapper;
vtkActor **coneActor;
vtkRenderer *ren1;
vtkRenderWindow *renWin;
FILE *fp;
int filenumber=0;
string last = ".txt";
string photot = ".bmp";
/*
vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
void inint()
{
	filter->SetInput(renWin);
}
*/
void wirtebmp()
{
	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(renWin);
	vtkBMPWriter *writer = vtkBMPWriter::New();
	string nowname = "E:\\manybmp\\" +to_string(filenumber)+ photot;
	writer->SetFileName(nowname.data());
	writer->SetInputConnection(filter->GetOutputPort());
	writer->Write();
	writer->Update();
}
void inintsphere()
{
	renWin = vtkRenderWindow::New();
	cone = (vtkSphereSource**)malloc(sizeof(vtkSphereSource*) * allnumber);
	coneMapper = (vtkPolyDataMapper**)malloc(sizeof(vtkPolyDataMapper*) * allnumber);
	coneActor = (vtkActor**)malloc(sizeof(vtkActor*) * allnumber);
	for (int i = 0;i < allnumber;i++)
	{
		cone[i]= vtkSphereSource::New();
		cone[i]->SetRadius(0.0145781);
		cone[i]->SetThetaResolution(3);
		cone[i]->SetPhiResolution(3);
		coneMapper[i] = vtkPolyDataMapper::New();
		coneMapper[i]->SetInputConnection(cone[i]->GetOutputPort());
		coneActor[i]= vtkActor::New();
		coneActor[i]->SetMapper(coneMapper[i]);
	}
	ren1 = vtkRenderer::New();
}
int addwater()
{
	for (int i = 0;i < allnumber;i++)
	{
		ren1->AddActor(coneActor[i]);
	}
	return 1;
}
int removewater()
{
	for (int i = 0;i < allnumber;i++)
	{
		cone[i]->Delete();
		coneMapper[i]->Delete();
		coneActor[i]->Delete();
	}
	ren1->Delete();
	renWin->Delete();
	return 1;
}
int inintfiles()
{
	int n;
	float temp;
	string filename = "E:\\bs\\particles_" + to_string(filenumber)+last;
	printf("%s\n", filename.data());
	fopen_s(&fp, filename.data(), "r");
	fscanf_s(fp, "%d %f", &n, &temp);
	//printf("%d", n);
	return 0;
}
int readfiles()
{
	inintfiles();
	for (int i = 0;i < allnumber;i++)
	{
		float x, y, z;
		fscanf_s(fp,"%f %f %f",&x,&y,&z);
		//printf("%f %f %f\n", x, y, z);
		cone[i]->SetCenter(x, y, z);
	}
	fclose(fp);
	return 1;
}
int main()
{
	inintsphere();
	//inint();
	addwater();
	ren1->SetBackground(0.1, 0.2, 0.4);
	renWin->AddRenderer(ren1);
	renWin->SetSize(300, 300);
	int i;
	ren1->GetActiveCamera()->SetPosition(1.5, 1.5, 1.5);
	ren1->GetActiveCamera()->SetFocalPoint(0.5, 0.5, 0.1);
	for (i = 0; i<=999;i++)
	{
		filenumber = i;
		readfiles();
		wirtebmp();
		renWin->Render();
	}
	removewater();
	return 0;
}



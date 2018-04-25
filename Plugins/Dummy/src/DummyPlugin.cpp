#include <DummyPlugin.hpp>

#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <QPushButton>
#include <string>

#include <Engine/RadiumEngine.hpp>
#include <DummySystem.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <Engine/Renderer/Mesh/Mesh.hpp>

namespace DummyPlugin {

	DummyPluginC::~DummyPluginC() {};

	void DummyPluginC::registerPlugin(const Ra::PluginContext& context)
	{
		m_frameCounter = 0;
		//Register a system here 
		DummySystem* system = new DummySystem(this);
		context.m_engine->registerSystem("DummySystem", system);
	}

	bool DummyPluginC::doAddWidget(QString & name)
	{
		//initialize name and return true if you wish to add a widget in the toolbox
		name = "Dummy !";
		return true;
	}

	QWidget * DummyPluginC::getWidget()
	{
		//create your widget here and return the pointer
		QWidget* widget = new QWidget;
		m_label = new QLabel("frames : "+m_frameCounter, widget);

		m_infoNbTriangle = new QLabel(widget);
		QPushButton* updateTri = new QPushButton("Update triangle count", widget);
		QObject::connect(updateTri, SIGNAL(clicked()), this, SLOT(updateNbTriangle()));

		QVBoxLayout* layout = new QVBoxLayout(widget);
		layout->addWidget(m_label);
		layout->addWidget(m_infoNbTriangle);
		layout->addWidget(updateTri);
		return widget;
	}

	bool DummyPluginC::doAddMenu()
	{
		//return true if you wish to add a menu
		return true;
	}

	QMenu * DummyPluginC::getMenu()
	{
		//create your menu here and return the pointer
		QMenu* menu = new QMenu("Dummy");

		QAction* a1 = menu->addAction("Hello there");
		QAction* a2 = menu->addAction("And there");

		CORE_UNUSED(a1);
		CORE_UNUSED(a2);

		return menu;
	}

	bool DummyPluginC::doAddAction(int & nb)
	{
		//return true if you wish to add action
		//set nb as the number of action button you wish to add
		nb = 1;
		return true;
	}

	QAction * DummyPluginC::getAction(int id)
	{
		//return the QAction corresponding to id
		return new QAction(QIcon(":/Assets/Images/RadiumIcon.png"), QString("Dummy action"), nullptr);
	}

	void DummyPluginC::incrementFrameCounter()
	{
		m_frameCounter += 1;
		std::string aff = "frames : " + std::to_string(m_frameCounter);
		QString qs = QString::fromStdString(aff);
		m_label->setText(qs);
	}

	void DummyPluginC::updateNbTriangle() {
		uint nbTriangle = 0;
		std::vector<std::shared_ptr<Ra::Engine::RenderObject>> objects;
		Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObjects(objects);
		for (auto ro : objects) {
			nbTriangle += ro->getMesh()->getGeometry().m_triangles.size();
		}
		std::string aff = "nb triangle : " + std::to_string(nbTriangle);
		QString qs = QString::fromStdString(aff);
		m_infoNbTriangle->setText(qs);
	}

}

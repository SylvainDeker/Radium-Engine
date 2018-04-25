#ifndef DUMMYPLUGIN_HPP_
#define DUMMYPLUGIN_HPP_

#include <QLabel>

#include <PluginBase/RadiumPluginInterface.hpp>

namespace DummyPlugin {
// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class DummyPluginC : public QObject, Ra::Plugins::RadiumPluginInterface {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "RadiumEngine.PluginInterface")
	Q_INTERFACES(Ra::Plugins::RadiumPluginInterface)

public:
	virtual ~DummyPluginC();

	void registerPlugin(const Ra::PluginContext& context) override;

	virtual bool doAddWidget(QString& name) override;
	virtual QWidget* getWidget() override;

	virtual bool doAddMenu() override;
	virtual QMenu* getMenu() override;

	virtual bool doAddAction(int& nb) override;
	virtual QAction* getAction(int id) override;

	void incrementFrameCounter();

public slots:
	void updateNbTriangle();

private:
	int m_frameCounter;
	QLabel* m_label;
	QLabel* m_infoNbTriangle;

};
}

#endif //DUMMYPLUGIN_HPP_


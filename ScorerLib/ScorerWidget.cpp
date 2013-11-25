#include "ScorerWidget.h"
#include "ui_ScorerWidget.h"
#include "../topo-blend/topo-blend.h"

ScorerWidget::ScorerWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::ScorerWidget)
{
	ui->setupUi(this);

	QVector<Structure::Graph*> empty;
	s_manager = new ScorerManager( NULL, NULL, empty );

	// Compute
	s_manager->connect(ui->parseConstraintPair, SIGNAL(clicked()), SLOT(parseConstraintPair()));
    s_manager->connect(ui->parseGlobalSymm, SIGNAL(clicked()), SLOT(parseGlobalReflectionSymm()));
	s_manager->connect(ui->parseConstraintGroup, SIGNAL(clicked()), SLOT(parseConstraintGroup()));
	
	// Evaluate
    s_manager->connect(ui->evaluateGlobalSymm, SIGNAL(clicked()), SLOT(evaluateGlobalReflectionSymm()));
	s_manager->connect(ui->evaluateGlobalSymmAuto, SIGNAL(clicked()), SLOT(evaluateGlobalReflectionSymmAuto()));

	s_manager->connect(ui->evaluateTopology, SIGNAL(clicked()), SLOT(evaluateTopology()));
	s_manager->connect(ui->evaluateTopologyAuto, SIGNAL(clicked()), SLOT(evaluateTopologyAuto()));	

	s_manager->connect(ui->evaluatePairs, SIGNAL(clicked()), SLOT(evaluatePairs()));
	s_manager->connect(ui->evaluatePairsAuto, SIGNAL(clicked()), SLOT(evaluatePairsAuto()));	

	s_manager->connect(ui->evaluateGroups, SIGNAL(clicked()), SLOT(evaluateGroups()));
	s_manager->connect(ui->evaluateGroupsAuto, SIGNAL(clicked()), SLOT(evaluateGroupsAuto()));

	// Options
    s_manager->connect(ui->bUseSourceCenter, SIGNAL(clicked(bool)), SLOT(setIsUseSourceCenter(bool)));
}

ScorerWidget::~ScorerWidget()
{
	delete ui;
}


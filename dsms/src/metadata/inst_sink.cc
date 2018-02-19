#ifndef _PLAN_MGR_IMPL_
#include "../../include/metadata/plan_mgr_impl.h"
#endif

#ifndef _SINK__
#include "../../include/execution/operators/sink.h"
#endif

using namespace Metadata;
using Execution::Sink;

int PlanManagerImpl::inst_sink (Physical::Operator *op)
{
	Sink *sink;
	
	ASSERT (op);
	ASSERT (op -> kind == PO_SINK);
	
	sink = new Sink(op -> id, LOG);
	op -> instOp = sink;
	
	return 0;
}


#pragma once

#include "moja/flint/iflintdata.h"
#include "moja/flint/record.h"
#include "moja/flint/recordaccumulator.h"

#include <moja/dynamic.h>

#include "moja/datetime.h"

namespace moja::flint {

class UncertaintySimulationUnitData : public flint::IFlintData {
  public:
   UncertaintySimulationUnitData()
       : local_domain_id(-1),
         land_unit_area(0.0),
         location_id(-1),
         process_unit_count(0),
         lu_count_processing_unit(0),
         lu_count_local_domain(0) {}

   virtual ~UncertaintySimulationUnitData() = default;
   UncertaintySimulationUnitData(const UncertaintySimulationUnitData&) = delete;
   UncertaintySimulationUnitData& operator=(const UncertaintySimulationUnitData&) = delete;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override {}

   DynamicVar getProperty(const std::string& key) const override;

   // Common data
   int local_domain_id;
   double land_unit_area;

   // Collection record ids
   Int64 location_id;

   // Collections shared within a thread
   RecordAccumulator<UncertaintyFluxRow> flux_results;
   RecordAccumulatorMap2<UncertaintyStockRow, UncertaintyStockTuple, UncertaintyStockRecordConverter,
                         UncertaintyStockKey, UncertaintyStockValue>
       stock_results;

   // -- Run Stats
   int process_unit_count;
   Int64 lu_count_processing_unit;
   Int64 lu_count_local_domain;

   DateTime start_system_time;
   DateTime end_system_time;
   DateTime start_local_domain_time;
   DateTime end_local_domain_time;
   DateTime start_processing_unit_time;
   DateTime end_processing_unit_time;
};

inline DynamicVar UncertaintySimulationUnitData::getProperty(const std::string& key) const { return DynamicVar(); }

} // namespace moja


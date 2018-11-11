import logging
from gym.envs.registration import register

logger = logging.getLogger(__name__)

register(
    id='Microgrid-beta-v1',
    entry_point='custom_microgrid.custom_microgrid_3_agents:SecondaryController',
)